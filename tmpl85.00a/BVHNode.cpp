#include "template.h"
#include "BVHNode.h"

void BVHNode::subdivide(BVH* bvh, unsigned int* poolIndex) {
	if (count <= 3) {
		return;
	}
	left = &bvh->pool[(*poolIndex)++];
	right = &bvh->pool[(*poolIndex)++];
	partition(bvh);

	left->subdivide(bvh, poolIndex);
	right->subdivide(bvh, poolIndex);
	isLeaf = false;

}

void maxBound(AABB* aabb, const AABB* check) {
	aabb->leftBottom.x = min(check->leftBottom.x, aabb->leftBottom.x);
	aabb->leftBottom.y = min(check->leftBottom.y, aabb->leftBottom.y);
	aabb->leftBottom.z = min(check->leftBottom.z, aabb->leftBottom.z);

	aabb->rightTop.x = max(check->rightTop.x, aabb->rightTop.x);
	aabb->rightTop.y = max(check->rightTop.y, aabb->rightTop.y);
	aabb->rightTop.z = max(check->rightTop.z, aabb->rightTop.z);
}


void BVHNode::partition(BVH* bvh) {
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
	bool yAxis = false;
	bool zAxis = false;

	for (int i = first; i < first + count; i++) {
		Triangle* t = bvh->getTriangleByIndice(i);
		glm::vec3 centroid = t->centroid;
		int xCounter = 0;
		int yCounter = 0;
		int zCounter = 0;
		//float xsurfaceAreaLeft = t->getBounds().surfaceArea();
		float xsurfaceAreaLeft = 0;
		float xsurfaceAreaRight = 0;

		//float ysurfaceAreaLeft = t->getBounds().surfaceArea();
		float ysurfaceAreaLeft = 0;
		float ysurfaceAreaRight = 0;

		//float zsurfaceAreaLeft = t->getBounds().surfaceArea();
		float zsurfaceAreaLeft = 0;
		float zsurfaceAreaRight = 0;
		for (int y = first; y < first + count; y++) {
			Triangle* temp = bvh->getTriangleByIndice(y);
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
			if (temp->centroid.y <= centroid.y) {
				//left
				yCounter++;
				ysurfaceAreaLeft += temp->getBounds().surfaceArea();
			}
			else {
				//right
				ysurfaceAreaRight += temp->getBounds().surfaceArea();
			}
			//zsplit
			if (temp->centroid.z <= centroid.z) {
				//left
				zCounter++;
				zsurfaceAreaLeft += temp->getBounds().surfaceArea();
			}
			else {
				//right
				zsurfaceAreaRight += temp->getBounds().surfaceArea();
			}
		}
		float xDifference = abs(xsurfaceAreaLeft - xsurfaceAreaRight);
		float yDifference = abs(ysurfaceAreaLeft - ysurfaceAreaRight);
		float zDifference = abs(zsurfaceAreaLeft - zsurfaceAreaRight);
		if (xDifference < lowestDifference) {
			lowestDifference = xDifference;
			bestCentroid = centroid;
			bestLeftCount = xCounter;
			xAxis = true;
			yAxis = false;
			zAxis = false;//y false and z false
		}
		if (yDifference < lowestDifference) {
			lowestDifference = yDifference;
			bestCentroid = centroid;
			bestLeftCount = yCounter;
			xAxis = false;
			yAxis = true;
			zAxis = false;
		}
		if (zDifference < lowestDifference) {
			lowestDifference = zDifference;
			bestCentroid = centroid;
			bestLeftCount = zCounter;
			xAxis = false;
			yAxis = false;
			zAxis = true;
		}
		//y and z aswell
	}
	//Recalculate for some reason well mostly because it needs to change and I am lazy
	//might actually interesting to keep it like this since bounds will only be calculated once than
	//int indicesMiddle = first + bestLeftCount - 1;
	//setIndice(bestIndice, indicesMiddle);
	//left->first = bestIndice;
	int leftIndice = 0;// first;
	int rightIndice = count - 1; // first + count - 1;
								 //for swapping
								 //int* indices = getIndices();
	AABB aabbLeft, aabbRight;
	unsigned int* backup = new unsigned int[count];
	for (int i = 0; i < count; i++) {
		backup[i] = bvh->indices[first + i];
	}

	for (int i = first; i < first + count; i++) {
		//if (i != bestIndice) {
		Triangle* temp = bvh->getTriangleByIndice(i);
		//xsplit
		bool left = false;
		if (xAxis) {
			left = temp->centroid.x <= bestCentroid.x;
		}
		if (yAxis) {
			left = temp->centroid.y <= bestCentroid.y;
		}
		if (zAxis) {
			left = temp->centroid.z <= bestCentroid.z;
		}
		if (left) {
			//left
			//swapping is an issue
			//bvh->setIndice(leftIndice, i);
			backup[leftIndice] = bvh->indices[i];
			leftIndice++;
			maxBound(&aabbLeft, &temp->getBounds());
		}
		else {
			//right
			//bvh->setIndice(rightIndice, i);
			backup[rightIndice] = bvh->indices[i];
			rightIndice--;
			maxBound(&aabbRight, &temp->getBounds());
		}
		//}
	}
	//overwrite values;
	for (int i = 0; i < count; i++) {
		bvh->indices[first + i] = backup[i];
	}
	//not sure if required since local variable but yea 
	delete[] backup;

	left->first = first;
	left->count = bestLeftCount;
	left->bounds = aabbLeft;
	right->first = first+rightIndice+1; //first+count-bestLeftCount;
	right->count = count - bestLeftCount;
	right->bounds = aabbRight;
}

AABB BVHNode::calculateBoundsNode(BVHNode* node, Triangle** objects) {
	AABB box = AABB(glm::vec3(INFINITE, INFINITE, INFINITE), glm::vec3(-INFINITE, -INFINITE, -INFINITE));
	for (int indice = node->first; indice < node->first + node->count; indice++) {

		AABB temp = (*(objects + indice))->getBounds();
		box.leftBottom.x = min(temp.leftBottom.x, box.leftBottom.x);
		box.leftBottom.y = min(temp.leftBottom.y, box.leftBottom.y);
		box.leftBottom.z = min(temp.leftBottom.z, box.leftBottom.z);

		box.rightTop.x = max(temp.rightTop.x, box.rightTop.x);
		box.rightTop.y = max(temp.rightTop.y, box.rightTop.y);
		box.rightTop.z = max(temp.rightTop.z, box.rightTop.z);
	}
	return box;
}

void BVHNode::traverse(Ray* r, unsigned int pointert, BVH* bvh, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance) {
	if (!bounds.intersects(r)) {
		return;
	}
	if (isLeaf) {//isLeaf
		intersectTriangles(*r, bvh, intersection, normal, material, distance);
	}
	else {
		//bvh->pool[pointert++].traverse(r, pointert, bvh, intersection, normal, material, distance);
		left->traverse(r, pointert, bvh, intersection, normal, material, distance);
		right->traverse(r, pointert, bvh, intersection, normal, material, distance);
		//bvh->pool[pointert++].traverse( r, pointert, bvh, intersection, normal, material, distance );
	}
}

void BVHNode::traverse(Ray* r, unsigned int pointert, BVH* bvh, float* distance) {
	if (!bounds.intersects(r)) {
		return;
	}
	if (isLeaf) {//isLeaf
		intersectTriangles(*r, bvh, distance);
	}
	else {
		bvh->pool[pointert++].traverse(r, pointert, bvh, distance);
		bvh->pool[pointert++].traverse(r, pointert, bvh, distance);
	}
}

void BVHNode::intersectTriangles(const Ray r, BVH* bvh, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance) {
	float tempDistance = INFINITY;
	//*distance = INFINITY;
	for (int i = first; i < first + count; i++) {
		Triangle* triangle = bvh->getTriangleByIndice(i);
		glm::vec3 temp = triangle->intersection(r, &tempDistance);
		if(tempDistance < *distance){
			*normal = temp;
			*distance = tempDistance;
			*material = *triangle->material;
		}
		
	}
}

void BVHNode::intersectTriangles(const Ray r, BVH* bvh, float* distance) {
	float tempDistance = INFINITY;
	//*distance = INFINITY;
	for (int i = first; i < first + count; i++) {
		Triangle* triangle = bvh->getTriangleByIndice(i);
		triangle->intersection(r, &tempDistance);
		if (tempDistance < *distance) {
			*distance = tempDistance;
		}
	}
}