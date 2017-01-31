#include "../shared.h"
#include "randomnumbers.h"
#include "raytracer.h"

#include "../RayCL.h"
#include "../TriangleCL.h"
#include "../LightCL.h"
#include "../BVHNodeCL.h"
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
	return (float3)(1, 1, 1);
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
			float a = dot(normal, direction);
			if (a < 0) {
				a *= -1;
			}
	//		printf("OCL: %f\n", distance);
			c += lights[i].color * calculateStrength(lights[i], distance) * a; //**angle;
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

// http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
bool bbIntersects(struct Ray* r, struct BVHNodeStruct bvhNode, float* distance) {
	// r->dir is unit direction vector of ray
	float3 dirfrac;
	/*float3 unit = r->direction - r->origin;
	unit = normalize(unit);
	printf("dir %f,%f,%f", r->direction.x, r->direction.y, r->direction.z);
	printf("dir1 %f,%f,%f", unit.x, unit.y, unit.z);*/
	dirfrac.x = 1.0f / r->direction.x;
	dirfrac.y = 1.0f / r->direction.y;
	dirfrac.z = 1.0f / r->direction.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r->org is origin of ray
	float t1 = (bvhNode.leftBottom.x - r->origin.x)*dirfrac.x;
	float t2 = (bvhNode.rightTop.x - r->origin.x)*dirfrac.x;
	float t3 = (bvhNode.leftBottom.y - r->origin.y)*dirfrac.y;
	float t4 = (bvhNode.rightTop.y - r->origin.y)*dirfrac.y;
	float t5 = (bvhNode.leftBottom.z - r->origin.z)*dirfrac.z;
	float t6 = (bvhNode.rightTop.z - r->origin.z)*dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		*distance = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		*distance = tmax;
		return false;
	}
	//printf("tmin %f, tmax %f", tmin, tmax);
	*distance = tmin;
	//r->bvhHit++;
	return true;

}

void nearestIntersectionBVH(struct Ray* r, __global struct Triangle* objects, int amountOfObjects, float4* color, __global struct BVHNodeStruct* bvhNodes, __global unsigned int* bvhIndices, __global int* stack, float3* normal) {

	int pointer = 0;
	stack[pointer++] = 0; //initialize;
	bool notDone = false;
	struct BVHNodeStruct bvhNode;

	bvhNode = bvhNodes[0];
	//printf("bvhNode 0, %d,%d", bvhNode.count, bvhNode.leftFirst);
	printf("bvh 0 count %d, index %d", bvhNode.count, bvhNode.leftFirst);
	bvhNode = bvhNodes[1];
	printf("bvh 1 count %d, index %d", bvhNode.count, bvhNode.leftFirst);


	while(notDone) {
		printf("pointer %d, %d", pointer, stack[1]);
		bvhNode = bvhNodes[stack[pointer-1]];
		//printf("leftBottom (%f, %f, %f), rightTop (%f, %f, %f), p %d", bvhNode.leftBottom.x, bvhNode.leftBottom.y, bvhNode.leftBottom.z, bvhNode.rightTop.x, bvhNode.rightTop.y, bvhNode.rightTop.z, pointer);
		//printf("bvh reached count %d, index %d", bvhNode.count, bvhNode.leftFirst);
		if (pointer > 2 * amountOfObjects) {// safety
			printf("pointer is too high %d", pointer);
			return;
		}
		//printf("OCL: objects (%f,%f,%f)", objects[0].v1.x, objects[0].v1.y, objects[0].v1.z);
		float distance = MAXVALUE;

		//float tempDistance = MAXVALUE;
		if (!bbIntersects(r, bvhNode, &distance)) {
			//printf(" doesn't interesect leftBottom (%f, %f, %f), rightTop (%f, %f, %f), p %d", bvhNode.leftBottom.x, bvhNode.leftBottom.y, bvhNode.leftBottom.z, bvhNode.rightTop.x, bvhNode.rightTop.y, bvhNode.rightTop.z, pointer);
			pointer--;
			if (pointer < 0) {
				notDone = false;
				return;
			}

		}
		if (bvhNode.count != 0) {//isLeaf
			printf("leaf is reached count %d, index %d", bvhNode.count, bvhNode.leftFirst);
			for (int i = bvhNode.leftFirst; i < bvhNode.leftFirst + bvhNode.count; i++) {
				distance = r->t;
				intersection(r, objects[bvhIndices[i]]);
				if (r->t != distance) {//closer than last one
					*normal = objects[bvhIndices[i]].direction;
					//printf("OCL: material (%f,%f,%f)", objects[i].color.x, objects[i].color.y, objects[i].color.z);
					*color = objects[bvhIndices[i]].color;
					//material->reflectioness = objects[i].reflectioness;
					printf("OCL: material (%f,%f,%f)", color->x, color->y, color->z);
					
					notDone = false;
				}
			}

		}
		else {
			//
			printf("else count %d, index %d", bvhNode.count, bvhNode.leftFirst);
			stack[pointer++] = bvhNode.leftFirst;
			stack[pointer++] = bvhNode.leftFirst+1;
		}
	}

}

float3 Trace(int x, int y, float3 pos, float3 direction, __global struct Triangle* triangles, int amountOfTriangles, __global struct Light* lights, int amountOfLights, __global struct BVHNodeStruct* bvhNodes, __global unsigned int* bvhIndices, __global int* stack)
{
	struct Ray r = GeneratePrimaryRay(x, y, pos, direction);
	//printf("OCL: ray direction (%f,%f,%f)", r.direction.x, r.direction.y, r.direction.z);
	//struct Material material;
	//float3 color = (float3)(0, 0, 0, 0);
	float4 material = (float4)(0,0,0,0);
	for(int bounces = 0; bounces < MAXBOUNCES; bounces++){
//#if 0
	//	float3 normal = nearestIntersection(&r, triangles, amountOfTriangles, &material);
//#else
		float3 normal;
		nearestIntersectionBVH(&r, triangles, amountOfTriangles, &material, bvhNodes, bvhIndices, stack, &normal);
//#endif
		float3 color = (float3)(material.x, material.y, material.z);
		if (r.t >= MAXVALUE) {
			return (float3)(0,0,0);
		}
		//printf("OCL: color (%f,%f,%f)", color.x, color.y, color.z);
		//printf("OCL: material (%f,%f,%f)", material.x, material.y, material.z);
		float3 intersection = r.origin + r.t * r.direction;

		float angle = -1;
		/* (material.w == 1) {
			//glm::vec3 reflect = r.getDirectiion() - 2.0f * glm::dot(r.getDirection(), normal) * normal;
			r.origin = intersection + 0.1f * Reflect(r.direction, normal);
			r.direction = Reflect(direction, normal);
			r.t = MAXVALUE;
			printf("OCL: reflective %f", material.w);
		}
		else {*/
			float3 mul = directIllumination(intersection, normal, triangles, amountOfTriangles, lights, amountOfLights, &angle);
			return color * mul; //color
		//}
	}
	int value = 1;
	printf("more than max bounces %d", value);
	return (0, 0, 0);

}
__kernel void TestFunction(write_only image2d_t outimg, float3 pos, float3 direction, __global struct Triangle* triangles, int amountOfTriangles, __global struct Light* lights, int amountOfLights, __global int* ints, __global struct BVHNodeStruct* bvhNode, __global unsigned int* indices, __global int* stack)
{
	uint x = get_global_id(0);
	uint y = get_global_id(1);
	const uint pixelIdx = x + y * SCRWIDTH;
	if (pixelIdx >= (SCRWIDTH * SCRHEIGHT)) return;
	//printf("I am starting %d", amountOfTriangles);
	// do calculations
	//printf("OCL: pos (%f,%f,%f)", pos.x, pos.y, pos.z);
	//printf("OCL: target (%f,%f,%f)", target.x, target.y, target.z);
	//printf("OCL: triangles v1(%f,%f,%f), v2(%f,%f,%f), v3(%f,%f,%f)", triangles.v1.x, triangles.v1.y, triangles.v1.z, triangles.v2.x, triangles.v2.y, triangles.v2.z, triangles.v3.x, triangles.v3.y, triangles.v3.z);
	//printf("OCL: triangle color (%f,%f,%f)", triangles[12].color.x, triangles[12].color.y, triangles[12].color.z);

	printf("OCL:bvh 1 count %d, index %d", bvhNode[1].count, bvhNode[1].leftFirst);
	float3 color;// = Trace(x, y, pos, direction, triangles, amountOfTriangles, lights, amountOfLights, bvhNode, indices, stack);
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