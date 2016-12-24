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

extern class BVH;

class BVHNode {
protected:
	void intersectTriangles(const Ray r, BVH* bvh, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance);
	void intersectTriangles(const Ray r, BVH* bvh, float* distance);
public:
	AABB bounds;	
	//BVHNode* left;
	//BVHNode* right;
	//bool isLeaf = true;
	int left;
	int first, count;

	BVHNode() {  }
	void subdivide(BVH* bvh, unsigned int* poolIndex);
	void partition(BVH* bvh);
	AABB calculateBoundsNode(BVHNode* node, Triangle** objects);
	void traverse(Ray* r, unsigned int pointert, BVH* bvh, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance);
	void traverse(Ray* r, unsigned int pointert, BVH* bvh, float* distance);
};
