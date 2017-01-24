//#pragma once

#include "MaterialCL.h"

struct Triangle {
	float3 v1, v2, v3; //vertices
	float3 direction; //normal

	float3 e1, e2; //precalculated (edge?) values

	struct Material material;
};