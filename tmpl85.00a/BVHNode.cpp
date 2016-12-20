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
	/*left->first = first;
	int middle = count * 0.5;
	left->count = middle;
	left->bounds = calculateBoundsNode(left, objects);
	right->first = first + middle;
	right->count = count - middle;
	right->bounds = calculateBoundsNode(right, objects);*/
	
	float lowestDifference = INFINITE;
	glm::vec3 bestCentroid;
	int bestLeftCount = -1;
	bool xAxis = false;

	for (int i = first; i < first + count; i++) {
		Triangle* t = getTriangle(i);
		glm::vec3 centroid = t->centroid;
		int xCounter = 0;
		float xsurfaceAreaLeft = t->getBounds().surfaceArea();
		float xsurfaceAreaRight = 0;
		for (int y = first; y < first + count; y++) {
			Triangle* temp = getTriangle(i);
			//xsplit
			if (temp->centroid.x <= centroid.x) {
				//left
				xCounter++;
				xsurfaceAreaLeft += temp->getBounds().surfaceArea();
			}
			else {
				//right
				xsurfaceAreaRight += temp->getBounds().surfaceArea();
			}
			//ysplit
			//zsplit
		}
		float xDifference = abs(xsurfaceAreaLeft - xsurfaceAreaRight);
		if (xDifference < lowestDifference) {
			lowestDifference = xDifference;
			bestCentroid = centroid;
			bestLeftCount = xCounter;
			xAxis = true;
			//y false and z false
		}
		//y and z aswell
	}
	//Recalculate for some reason well mostly because it needs to change and I am lazy
	if (xAxis) {
		//int indicesMiddle = first + bestLeftCount - 1;
		//setIndice(bestIndice, indicesMiddle);
		//left->first = bestIndice;
		int leftIndice = first;
		int rightIndice = first + count-1;
		//for swapping
		//int* indices = getIndices();
		AABB aabbLeft, aabbRight;
		for (int i = first; i < first + count; i++) {
			//if (i != bestIndice) {
				Triangle* temp = getTriangle(i);
				//xsplit
				if (temp->centroid.x <= bestCentroid.x) {
					//left
					//swapping is an issue
					setIndice(leftIndice, i);
					leftIndice++;
					maxBound(aabbLeft, temp->getBounds());
				}
				else {
					//right
					setIndice(rightIndice, i);
					rightIndice--;
					maxBound(aabbRight, temp->getBounds());
				}
			//}
		}
		left->first = first;
		left->count = bestLeftCount;
		left->bounds = aabbLeft;
		right->first = rightIndice; //first+count-bestLeftCount;
		right->count = count - bestLeftCount;
		left->bounds = aabbRight;
	}
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