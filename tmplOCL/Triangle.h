#pragma once
#include "system.h"
#include "material.h"

struct Triangle {
	cl_float3 v1, v2, v3; //vertices
	cl_float3 direction; //normal

	cl_float3 e1, e2; //precalculated (edge?) values

	Material material;
};

Triangle createTriangle(vec3 v1, vec3 v2, vec3 v3, Material material) {
	Triangle t;
	t.v1 = { v1.x, v1.y, v1.z };
	t.v2 = { v2.x, v2.y, v2.z };
	t.v3 = { v3.x, v3.y, v3.z };

	vec3 dir = normalize(cross((v2 - v1), (v3 - v1)));
	t.direction = { dir.x, dir.y, dir.z };

	vec3 e1 = v2 - v1;
	vec3 e2 = v3 - v1;
	t.e1 = { e1.x, e1.y, e1.z };
	t.e2 = { e2.x, e2.y, e2.z };
	t.material = material;
	return t;
}