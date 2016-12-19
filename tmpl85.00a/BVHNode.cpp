#include "template.h"
#include "BVHNode.h"

void BVHNode::subdivide(BVHNode* pool, BVH* bvh) {
	if (count < 3)	return;

	left = pool++;
	right = pool++;
	partition(bvh);

	left->subdivide(pool, bvh);
	right->subdivide(pool, bvh);
	isLeaf = false;
}

void BVHNode::partition(BVH* bvh) {
	//idk
	left->first = first;
	int middle = count * 0.5;
	left->count = middle;
	left->bounds = bvh->calculateBoundsNode(this);
	right->first = first + middle;
	right->count = count - middle;
}