#pragma once
#ifndef TRIANGLE
#define TRIANGLE


#include "system.h"
#include "material.h"

struct Triangle {
	cl_float3 v1, v2, v3; //vertices
	cl_float3 direction; //normal

	cl_float3 e1, e2; //precalculated (edge?) values

	//Material material;
	cl_float3 color;
};

Triangle createTriangle(vec3 v1, vec3 v2, vec3 v3, Material material);
Triangle createTriangle(vec3 v1, vec3 v2, vec3 v3, vec3 n1, vec3 n2, vec3 n3, Material material);
#endif // !TRIANGLE