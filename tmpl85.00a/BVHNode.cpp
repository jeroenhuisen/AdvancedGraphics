#include "template.h"
#include "BVHNode.h"

void BVHNode::subdivide(BVHNode* pool) {
	if (count < 3)	return;

	left = pool++;
	right = pool++;
	partition();

	left->subdivide(pool);
	right->subdivide(pool);
	isLeaf = false;
}

void BVHNode::partition() {
	//idk
	left->first = first;
	int middle = count * 0.5;
	left->count = middle;
	left->bounds = BVH::calculateBoundsNode(this);
	right->first = first + middle;
	right->count = count - middle;
}