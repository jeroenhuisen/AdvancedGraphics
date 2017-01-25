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