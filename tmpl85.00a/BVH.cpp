#include "template.h"

#include "BVH.h"

void BVH::constructBVH(Triangle* objects, int N) {
	// create index array
	indices = new unsigned int[N];
	for (int i = 0; i < N; i++) indices[i] = i;
	// allocate BVH root node
	pool = new BVHNode[N * 2 - 1];
	root = pool++;
	// subdivide root node
	//root->first = 0;
	root->count = N;
	root->bounds = calculateBounds(objects, 0, root->count);
	root->subdivide(pool);
}

AABB BVH::calculateBounds(Triangle* objects, int first, int count) {
	AABB box = AABB(glm::vec3(INFINITE, INFINITE, INFINITE), glm::vec3(-INFINITE, -INFINITE, -INFINITE));
	for (Triangle* tPtr = objects; tPtr < objects + count; tPtr++) {
		AABB temp = tPtr->getBounds();
		box.leftBottom.x = min(temp.leftBottom.x, box.leftBottom.x);
		box.leftBottom.y = min(temp.leftBottom.y, box.leftBottom.y);
		box.leftBottom.z = min(temp.leftBottom.z, box.leftBottom.z);

		box.rightTop.x = max(temp.rightTop.x, box.rightTop.x);
		box.rightTop.y = max(temp.rightTop.y, box.rightTop.y);
		box.rightTop.z = max(temp.rightTop.z, box.rightTop.z);
	}
	return box;
}