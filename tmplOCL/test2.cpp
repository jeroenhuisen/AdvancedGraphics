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
	float3 test = (p2 - p1);
	float3 test1 = test * 0.25f;
	float3 p = p1 + (p2 - p1) * fx + (p3 - p1) * fy;
	float3 O = float3(0, 0, 0);
	float3 D = (p - O);
	//r.t = 1e34f;
	D.x;
}