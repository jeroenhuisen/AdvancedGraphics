#include "../shared.h"
#include "randomnumbers.h"
#include "raytracer.h"

#include "../RayCL.h"
#include "../TriangleCL.h"
#include "../LightCL.h"


struct Ray GeneratePrimaryRay(int x, int y, float3 pos, float3 target) {
	struct Ray r;
	float3 E = normalize(target - pos);
	float3 up = (float3)(0, 1, 0); //y axis
	float3 right = normalize(cross(up, E));
	up = cross(E, right);
	
	float3 C = pos + E;
	float3 p1 = C - right + up; // top left
	float3 p2 = C + right + up; // top right
	float3 p3 = C - right - up; // bottom left

	float fx = (float)x / SCRWIDTH;
	float fy = (float)y / SCRHEIGHT;
	float3 P = p1 + (p2 - p1) * fx + (p3 - p1) * fy;

	r.direction = normalize(P - pos);//p-e
	r.origin = pos;
	r.t = 1e34f;
	return r;

}

void intersection(struct Ray* r, struct Triangle object ) {
	float3 P = cross(r->direction, object.e2);
	//printf("OCL: e2 (%f,%f,%f)", r->direction.x, r->direction.y, r->direction.z);
	float det = dot(object.e1, P);
	if ((det > -EPSILON) && (det < EPSILON)) {
		return; // Ray is either parallel to or inside the triangle
	}
	float inv_det = 1 / det;
	float3 T = r->origin - object.v1;
	float u = dot(T, P) * inv_det;
	if ((u < 0) || (u > 1)) {
		return; // Intersection lies outside of the triangle
	}
	float3 Q = cross(T, object.e1);
	float v = dot(r->direction, Q) * inv_det;
	if ((v < 0) || (u + v > 1)) {
		return; // Again, intersection outside of the triangle
	}
	float t = dot(object.e2, Q) * inv_det;
	if (t > 0) {
		r->t = min(r->t, t);
	}
}


float3 directIllumination(float3 intersection, float3 normal, struct Light lights, int amountOfLight, float* angle) {
	// simplify test
	return (float3)(1, 1, 1);
}

float3 nearestIntersection(struct Ray* r, struct Triangle objects, int amountOfObjects, float3* material) {
	float distance = -1;
	float3 normal;
	for (int i = 0; i < amountOfObjects; i++) {
		distance = r->t;
		/*intersection(r, objects[i]);
		if (r->t != distance) {//closer than last one
			normal = objects[i].direction;
			*material = objects[i].material;
		}*/
		intersection(r, objects);
		if (r->t != distance) {//closer than last one
			normal = objects.direction;
			*material = objects.color;
		}
	}
	return normal;

}

float3 Trace(int x, int y, float3 pos, float3 target, struct Triangle triangles, int amountOfTriangles, struct Light lights, int amountOfLights)
{
	struct Ray r = GeneratePrimaryRay(x, y, pos, target);
	//printf("OCL: ray direction (%f,%f,%f)", r.direction.x, r.direction.y, r.direction.z);
	int amountOfObjects = 1;
	//struct Material material;
	float3 color = (float3)(0, 0, 0);
	float3 normal = nearestIntersection(&r, triangles, amountOfObjects, &color);
	float3 intersection = r.origin + r.t * r.direction;

	float angle = -1;
	float3 mul = directIllumination(intersection, normal, lights, 0, &angle);

	return color * mul; //color
	//return (float3)(r.direction.x, r.direction.y, r.direction.z);

}
__kernel void TestFunction(write_only image2d_t outimg, float3 pos, float3 target, struct Triangle triangles, int amountOfTriangles, struct Light lights, int amountOfLights)
{
	uint x = get_global_id(0);
	uint y = get_global_id(1);
	const uint pixelIdx = x + y * SCRWIDTH;
	if (pixelIdx >= (SCRWIDTH * SCRHEIGHT)) return;
	// do calculations
	//printf("OCL: pos (%f,%f,%f)", pos.x, pos.y, pos.z);
	//printf("OCL: target (%f,%f,%f)", target.x, target.y, target.z);
	//printf("OCL: triangles v1(%f,%f,%f), v2(%f,%f,%f), v3(%f,%f,%f)", triangles.v1.x, triangles.v1.y, triangles.v1.z, triangles.v2.x, triangles.v2.y, triangles.v2.z, triangles.v3.x, triangles.v3.y, triangles.v3.z);
	float3 color = Trace(x, y, pos, target, triangles, amountOfTriangles, lights, amountOfLights);
	//float3 color = (float3)(x, y, 0);
	// send result to output array
	/*int r = (int)(clamp( color.x, 0.f, 1.f ) * 255.0f);
	int g = (int)(clamp( color.y, 0.f, 1.f ) * 255.0f);
	int b = (int)(clamp( color.z, 0.f, 1.f ) * 255.0f);*/
	float r = (clamp(color.x, 0.f, 1.f));
	float g = (clamp(color.y, 0.f, 1.f));
	float b = (clamp(color.z, 0.f, 1.f));

	write_imagef(outimg, (int2)(x, y), (float4)(r, g, b, 1));
}