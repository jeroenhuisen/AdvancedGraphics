#pragma once

#include "system.h"

#include "Triangle.h"
#include "BVHNode.h"
#ifndef A
#define A
#include "shared.h"

typedef class float3 {
public:
	float3() {};
	float3(float x, float y, float z): x(x), y(y), z(z) {  };
	float x;
	float y;
	float z;
	/*float3& operator+=(const float3& rhs)
	{
		// actual addition of rhs to *this
		return *this;
	}*/

};
float3 operator*(const float3 lhs, const float rhs);
float3 operator-(const float3 lhs, const float3 rhs);
float3 operator+(const float3 lhs, const float3 rhs);
extern void tester(int x, int y);
extern void GeneratePrimaryRay(int x, int y, vec3 pos, vec3 dir);
extern void nearestIntersectionBVH(Triangle* objects, int amountOfObjects, cl_float3* color, BVHNodeStruct* bvhNodes, unsigned int* bvhIndices, int* stack, cl_float3* normal);
#endif
