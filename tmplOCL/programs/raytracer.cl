#include "../shared.h"
#include "randomnumbers.h"
#include "raytracer.h"

#include "../RayCL.h"
#include "../TriangleCL.h"
#include "../LightCL.h"
//#include "../MaterialCL.h"

#define MAXVALUE 1e34f
#define MAXBOUNCES 10


struct Ray GeneratePrimaryRay(int x, int y, float3 pos, float3 direction) {
	struct Ray r;
	float3 E = normalize(direction - pos);
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
	r.t = MAXVALUE;
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

bool isThereAIntersection(struct Ray r, __global struct Triangle* objects, int amountOfObjects, const float distanceResult) {
	float distance = MAXVALUE;

	for (int i = 0; i < amountOfObjects; i++) {
		intersection(&r, objects[i]);

		//float floatError = 0.01; //otherwise black lines where it shouldnt be
		if (distance <= distanceResult ){//&& distance >= 0 + floatError) {
			return false;
		}
	}
	return true;
}

bool canReachLight(const float3 origin, const float3 direction, const float3 normal, __global struct Triangle* objects, int amountOfObjects, const float distanceResult) {

	struct Ray r;
	r.origin = origin + normal * 0.1f;
	r.direction = direction;

//#if SLOWBVH
	return isThereAIntersection(r, objects, amountOfObjects, distanceResult);
/*#else
	return scene->isThereAIntersectionBVH(r, distanceResult);
#endif*/

}


float3 directIllumination(float3 intersection, float3 normal, __global struct Triangle* objects, int amountOfObjects, __global struct Light* lights, int amountOfLights, float* angle) {
	// simplify test
	//return (float3)(1, 1, 1);
	float3 c = (float3)(0,0,0); //color
	//printf("OCL: %d\n", amountOfLight);
	for (int i = 0; i < amountOfLights; i++){
		float3 direction = lights[i].position - intersection;
		float distance = length(direction);
	//	printf("OCL: distance: %f\n", distance);
	//	printf("OCL: intersection: (%f,%f,%f)\n", intersection.x, intersection.y, intersection.z);
		direction = normalize(direction);
		
		if (canReachLight(intersection, direction, normal, objects, amountOfObjects, distance)) {
			
			*angle = max(0.0f,dot(normal, direction));
	//		printf("OCL: %f\n", distance);
			c += lights[i].color * calculateStrength(lights[i], distance) **angle;
			//
		}
	}
	//printf("ocl: c (%f, %f, %f)", c.x, c.y, c.z);
	return c;
	
}

float3 nearestIntersection(struct Ray* r, __global struct Triangle* objects, int amountOfObjects, float4* color) {
	//printf("OCL: objects (%f,%f,%f)", objects[0].v1.x, objects[0].v1.y, objects[0].v1.z);
	float distance = -1;
	float3 normal;
	for (int i = 0; i < amountOfObjects; i++) {
		distance = r->t;
		intersection(r, objects[i]);
		if (r->t != distance) {//closer than last one
			normal = objects[i].direction;
			//printf("OCL: material (%f,%f,%f)", objects[i].color.x, objects[i].color.y, objects[i].color.z);
			*color = objects[i].color;
			//material->reflectioness = objects[i].reflectioness;
			//printf("OCL: material (%f,%f,%f)", color->x, color->y, color->z);
		}
		/*intersection(r, objects);
		if (r->t != distance) {//closer than last one
			normal = objects.direction;
			*material = objects.color;
		}*/
	}
	return normal;

}

float3 Trace(int x, int y, float3 pos, float3 direction, __global struct Triangle* triangles, int amountOfTriangles, __global struct Light* lights, int amountOfLights)
{
	struct Ray r = GeneratePrimaryRay(x, y, pos, direction);
	//printf("OCL: ray direction (%f,%f,%f)", r.direction.x, r.direction.y, r.direction.z);
	//struct Material material;
	//float3 color = (float3)(0, 0, 0, 0);
	float4 material = (float4)(0,0,0,0);
	for(int bounces = 0; bounces < MAXBOUNCES; bounces++){
		float3 normal = nearestIntersection(&r, triangles, amountOfTriangles, &material);
		float3 color = (float3)(material.x, material.y, material.z);
		if (r.t >= MAXVALUE) {
			return (float3)(0,0,0);
		}
		//printf("OCL: color (%f,%f,%f)", color.x, color.y, color.z);
		//printf("OCL: material (%f,%f,%f)", material.x, material.y, material.z);
		float3 intersection = r.origin + r.t * r.direction;

		float angle = -1;
		if (material.w == 1) {
			//glm::vec3 reflect = r.getDirection() - 2.0f * glm::dot(r.getDirection(), normal) * normal;
			r.origin = intersection + 0.1f * Reflect(r.direction, normal);
			r.direction = Reflect(direction, normal);
			r.t = MAXVALUE;
			printf("OCL: reflective %f", material.w);
		}
		else {
			float3 mul = directIllumination(intersection, normal, triangles, amountOfTriangles, lights, amountOfLights, &angle);
			return color * mul; //color
		}
	}

}
__kernel void TestFunction(write_only image2d_t outimg, float3 pos, float3 direction, __global struct Triangle* triangles, int amountOfTriangles, __global struct Light* lights, int amountOfLights, __global int* ints)
{
	uint x = get_global_id(0);
	uint y = get_global_id(1);
	const uint pixelIdx = x + y * SCRWIDTH;
	if (pixelIdx >= (SCRWIDTH * SCRHEIGHT)) return;
	// do calculations
	//printf("OCL: pos (%f,%f,%f)", pos.x, pos.y, pos.z);
	//printf("OCL: target (%f,%f,%f)", target.x, target.y, target.z);
	//printf("OCL: triangles v1(%f,%f,%f), v2(%f,%f,%f), v3(%f,%f,%f)", triangles.v1.x, triangles.v1.y, triangles.v1.z, triangles.v2.x, triangles.v2.y, triangles.v2.z, triangles.v3.x, triangles.v3.y, triangles.v3.z);
	//printf("OCL: triangle color (%f,%f,%f)", triangles[12].color.x, triangles[12].color.y, triangles[12].color.z);

	float3 color = Trace(x, y, pos, direction, triangles, amountOfTriangles, lights, amountOfLights);
	//float3 color = (float3)(x, y, 0);
	// send result to output array
	/*int r = (int)(clamp( color.x, 0.f, 1.f ) * 255.0f);
	int g = (int)(clamp( color.y, 0.f, 1.f ) * 255.0f);
	int b = (int)(clamp( color.z, 0.f, 1.f ) * 255.0f);*/
	float r = (clamp(color.x, 0.f, 1.f));
	float g = (clamp(color.y, 0.f, 1.f));
	float b = (clamp(color.z, 0.f, 1.f));

	ints[0] = 2;

	write_imagef(outimg, (int2)(x, y), (float4)(r, g, b, 1));
}