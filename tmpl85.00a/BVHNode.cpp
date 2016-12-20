#include "template.h"
#include "BVHNode.h"

void BVHNode::subdivide(BVHNode* pool, Triangle* objects) {
	if (count < 3)	return;

	left = pool++;
	right = pool++;
	partition(objects);

	left->subdivide(pool, objects);
	right->subdivide(pool, objects);
	isLeaf = false;

}

void BVHNode::partition(Triangle* objects) {
	//idk
	left->first = first;
	int middle = count * 0.5;
	left->count = middle;
	left->bounds = calculateBoundsNode(left, objects);
	right->first = first + middle;
	right->count = count - middle;
	right->bounds = calculateBoundsNode(right, objects);
}

AABB BVHNode::calculateBoundsNode(BVHNode* node, Triangle* objects) {
	AABB box = AABB(glm::vec3(INFINITE, INFINITE, INFINITE), glm::vec3(-INFINITE, -INFINITE, -INFINITE));
	for (int indice = node->first; indice < node->first + node->count; indice++) {

		AABB temp = (objects + indice)->getBounds();
		box.leftBottom.x = min(temp.leftBottom.x, box.leftBottom.x);
		box.leftBottom.y = min(temp.leftBottom.y, box.leftBottom.y);
		box.leftBottom.z = min(temp.leftBottom.z, box.leftBottom.z);

		box.rightTop.x = max(temp.rightTop.x, box.rightTop.x);
		box.rightTop.y = max(temp.rightTop.y, box.rightTop.y);
		box.rightTop.z = max(temp.rightTop.z, box.rightTop.z);
	}
	return box;
}