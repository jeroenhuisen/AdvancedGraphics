#pragma once

#include "primitive.h"
#include "BVHNode.h"
#include "AABB.h"

class BVH {
//private:
public:
	BVHNode* root;
	BVHNode* pool;
	unsigned int* indices;
	Triangle** objects;

//public:
	void constructBVH(Triangle** objects, int N);
	AABB calculateBounds(Triangle** objects, int first, int count);
	//AABB calculateBoundsNode(BVHNode* node);

	Triangle* getTriangleByIndice(unsigned int indiceIndex);
	void setIndice(unsigned int index, unsigned int value);
};