#pragma once

#include "BVHNode.h"
#include "AABB.h"
#include "Triangle.h"

class BVH {
	//private:
public:
	BVHNodeStruct root;
	BVHNodeStruct* pool;
	unsigned int* indices;
	Triangle* objects;

	//public:
	void constructBVH(Triangle* objects, int N, unsigned int* poolIndex);
	AABB calculateBounds(Triangle* objects, int count);

	void subdivide(BVHNodeStruct* bvhNode, unsigned int* poolIndex, unsigned int* first);
	bool partition(BVHNodeStruct* bvhNode, int first);
	//AABB calculateBoundsNode(BVHNode* node);

	Triangle* getTriangleByIndice(unsigned int indiceIndex);
	//void setIndice(unsigned int index, unsigned int value);

	float surfaceArea(AABB aabb);
	glm::vec3 calcCentroid(Triangle* t);
	void maxBound(AABB* aabb, const AABB* check);
};

