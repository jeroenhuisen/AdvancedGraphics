#include "template.h"

#include "BVH.h"

void BVH::constructBVH(Primitive* objects, int N) {
	// create index array
	indices = new unsigned int[N];
	for (int i = 0; i < N; i++) indices[i] = i;
	// allocate BVH root node
	root = new BVHNode();
	// subdivide root node
	//root->first = 0;
	root->count = N;
	root->bounds = calculateBounds(objects, 0, root->count);
	root->subdivide();
}

AABB BVH::calculateBounds(Primitive* objects, int first, int count) {
	AABB box = AABB(glm::vec3(INFINITE, INFINITE, INFINITE), glm::vec3(-INFINITE, -INFINITE, -INFINITE));
	for (int i = first; i < count; i++) {
		AABB temp = objects[i].getBounds();
		box.leftBottom.x = min(temp.leftBottom.x, box.leftBottom.x);
		box.leftBottom.y = min(temp.leftBottom.y, box.leftBottom.y);
		box.leftBottom.z = min(temp.leftBottom.z, box.leftBottom.z);

		box.rightTop.x = min(temp.rightTop.x, box.rightTop.x);
		box.rightTop.y = min(temp.rightTop.y, box.rightTop.y);
		box.rightTop.z = min(temp.rightTop.z, box.rightTop.z);
	}
	return box;
}