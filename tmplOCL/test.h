#pragma once

#include "system.h"
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
#endif