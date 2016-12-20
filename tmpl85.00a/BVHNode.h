#pragma once
#include "AABB.h"
#include "Triangle.h"

/*struct BVHNode
{
	AABB bounds;	// 24 byes
	int leftFirst;	// 4 bytes
	int first;		// 4 bytes, total 32 bytes
};*/

/*BVHNode::Traverse(Ray r) {
	if (!r.Intersects(bounds)) return
		;
	if
		(isleaf())
	{
		IntersectPrimitives();
	}
	else {
		pool[left].Traverse(r);
		pool[left + 1].Traverse(r);
	}
}*/

class BVHNode {
public:
	AABB bounds;	
	BVHNode* left;
	BVHNode* right;
	bool isLeaf = true;
	int first, count;

	BVHNode() {  }
	void subdivide(BVHNode* pool, Triangle* objects);
	void partition(Triangle* objects);
	AABB calculateBoundsNode(BVHNode* node, Triangle* objects);
};
