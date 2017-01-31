#include "system.h"
#include "test.h"
float3 operator*(const float3 lhs, const float rhs)
{
	return  float3(lhs.x * rhs, lhs.y *rhs, lhs.z*rhs);
}
float3 operator-(const float3 lhs, const float3 rhs)
{
	return  float3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
float3 operator+(const float3 lhs, const float3 rhs)
{
	return  float3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
void tester(int x, int y) {
	float3 p1 = float3(-1, -1, -1); // top left
	float3 p2 = float3(1, -1, -1); // top right
	float3 p3 = float3(-1, 1, -1); // bottom left
	float fx = (float)x / (float)SCRWIDTH;
	float fy = (float)y / (float)SCRHEIGHT;
	float3 p = p1 + (p2 - p1) * fx + (p3 - p1) * fy;
	float3 O = float3(0, 0, 0);
	float3 D = (p - O);
	//r.t = 1e34f;
}

void GeneratePrimaryRay(int x, int y, vec3 pos, vec3 target) {
	vec3 E = normalize(target - pos);
	vec3 up = vec3(0.0f, 1.0f, 0.0f); //y axis
	vec3 right = normalize(cross(up, E));
	up = cross(E, right);

	vec3 C = pos + E;
	vec3 p1 = C - right + up; // top left
	vec3 p2 = C + right + up; // top right
	vec3 p3 = C - right - up; // bottom left

	float fx = (float)x / SCRWIDTH;
	float fy = (float)y / SCRHEIGHT;
	vec3 P = p1 + (p2 - p1) * fx + (p3 - p1) * fy;

	//vec3 direction = normalize(P - E);
	vec3 direction = normalize(P - pos);
	vec3 origin = pos;
	vec3 t= 1e34f;
}



void nearestIntersectionBVH(struct Triangle* objects, int amountOfObjects, cl_float3* color, BVHNodeStruct* bvhNodes, unsigned int* bvhIndices, int* stack, cl_float3* normal) {

	int pointer = 0;
	stack[pointer++] = 0; //initialize;
	bool notDone = true;
	BVHNodeStruct bvhNode;

	//bvhNode = bvhNodes[0];
	//printf("bvhNode 0, %d,%d", bvhNode.count, bvhNode.leftFirst);
	//printf("bvh 0 count %d, index %d", bvhNode.test.y, bvhNode.test.x);
	//bvhNode = bvhNodes[7];
	//printf("bvh 1 count %d, index %d", bvhNode.test.y, bvhNode.test.x);


	while (notDone) {
		//printf("pointer %d, %d", pointer, stack[(pointer - 1)]);
		bvhNode = bvhNodes[stack[(pointer - 1)]];
		//printf("leftBottom (%f, %f, %f), rightTop (%f, %f, %f), p %d", bvhNode.leftBottom.x, bvhNode.leftBottom.y, bvhNode.leftBottom.z, bvhNode.rightTop.x, bvhNode.rightTop.y, bvhNode.rightTop.z, pointer);
		//printf("bvh reached count %d, index %d", bvhNode.count, bvhNode.leftFirst);
		if (pointer > 24) {// safety
			printf("A pointer is too high %d, %d\n", pointer - 1, stack[(pointer - 2)]);
			printf("B pointer is too high %d, %d\n", pointer, stack[(pointer - 1)]);
			return;
		}
		//printf("OCL: objects (%f,%f,%f)", objects[0].v1.x, objects[0].v1.y, objects[0].v1.z);
		float distance = INFINITY;

		//float tempDistance = MAXVALUE;
		bool test = true;
		if (!test) { //no intersection
													//printf(" doesn't interesect leftBottom (%f, %f, %f), rightTop (%f, %f, %f), p %d", bvhNode.leftBottom.x, bvhNode.leftBottom.y, bvhNode.leftBottom.z, bvhNode.rightTop.x, bvhNode.rightTop.y, bvhNode.rightTop.z, pointer);
			if (pointer > 1) {
				printf(" doesn't interesect leftBottom (%f, %f, %f), rightTop (%f, %f, %f), p %d\n", bvhNode.leftBottom.x, bvhNode.leftBottom.y, bvhNode.leftBottom.z, bvhNode.rightTop.x, bvhNode.rightTop.y, bvhNode.rightTop.z, pointer);
				return;
			}
			pointer--;
			if (pointer < 1) {
				notDone = false;
				return;
			}

		}
		else { // intersection
			if (bvhNode.test.y != 0) {//isLeaf
				printf("leaf is reached count %d, index %d\n", bvhNode.test.y, bvhNode.test.x);
				for (int i = bvhNode.test.x; i < bvhNode.test.x + bvhNode.test.y; i++) {
					//distance = r->t;
					//intersection(r, objects[bvhIndices[i]]);
					//if (r->t != distance) {//closer than last one
						*normal = objects[bvhIndices[i]].direction;
						//printf("OCL: material (%f,%f,%f)", objects[i].color.x, objects[i].color.y, objects[i].color.z);
						*color = objects[bvhIndices[i]].color;
						//material->reflectioness = objects[i].reflectioness;
						printf("OCL: material (%f,%f,%f)\n", color->x, color->y, color->z);

						notDone = false;
						return;
					//}
				}

			}
			else {
				//
				printf("else count %d, index %d\n", bvhNode.test.y, bvhNode.test.x);
				//printf("pointerA %d, %d", pointer, stack[pointer]);
				stack[pointer - 1] = bvhNode.test.x;
				//printf("pointerB %d, %d", pointer, stack[pointer-1]);
				stack[pointer++] = bvhNode.test.x + 1;
				//printf("pointerC %d, %d", pointer, stack[pointer - 1]);
			}
		}
	}

}