#pragma once

#include "object.h"
#include "BVHNode.h"
#include "AABB.h"

class BVH {
private:
	BVHNode* root;
	unsigned int* indices;
public:
	void constructBVH(Object* objects, int N);
	AABB calculateBounds(Object* objects, int first, int count);
};