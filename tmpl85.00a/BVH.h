#pragma once

#include "primitive.h"
#include "BVHNode.h"
#include "AABB.h"

class BVH {
private:
	BVHNode* root;
	unsigned int* indices;
public:
	void constructBVH(Primitive* objects, int N);
	AABB calculateBounds(Primitive* objects, int first, int count);
};