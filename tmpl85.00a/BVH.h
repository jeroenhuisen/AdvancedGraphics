#pragma once

#include "primitive.h"
#include "BVHNode.h"
#include "AABB.h"

class BVH {
private:
	BVHNode* root;
	BVHNode* pool;
	unsigned int* indices;

public:
	void constructBVH(Triangle* objects, int N);
	AABB calculateBounds(Triangle* objects, int first, int count);
	AABB calculateBoundsNode(BVHNode* node);
};