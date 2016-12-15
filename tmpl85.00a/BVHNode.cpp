#include "template.h"
#include "BVHNode.h"

void BVHNode::subdivide() {
	if (count < 3) return;
	left = new BVHNode();
	right = new BVHNode();
	partition();

	left->subdivide();
	right->subdivide();
	isLeaf = false;
}

void BVHNode::partition() {
	//idk
}