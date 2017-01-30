#include "system.h"

#include "BVH.h"

void BVH::constructBVH(Triangle* objects, int N) {
	// create index array
	indices = new unsigned int[N];
	for (int i = 0; i < N; i++) indices[i] = i;//ISNT USED YET>
											   // allocate BVH root node
	pool = new BVHNodeStruct[N * 2 - 1];
	unsigned int poolIndex = 0;
	unsigned int indicesIndex = 0;
	root = pool[poolIndex++];

	// objects stored
	this->objects = objects;

	// subdivide root node
	root.leftFirst = 1;
	root.count = N;
	AABB bounds = calculateBounds(objects, root.count);//root->calculateBoundsNode(root, objects); 
	root.leftBottom = { bounds.leftBottom.x, bounds.leftBottom.y, bounds.leftBottom.z };
	root.rightTop = { bounds.rightTop.x, bounds.rightTop.y, bounds.rightTop.z };
	subdivide(&root, &poolIndex, &indicesIndex);
}

AABB BVH::calculateBounds(Triangle* objects, int count) {
	AABB box = AABB(glm::vec3(INFINITE, INFINITE, INFINITE), glm::vec3(-INFINITE, -INFINITE, -INFINITE));
	int i = 0;
	for (Triangle* tPtr = objects; tPtr < objects + count; tPtr++) {
		AABB temp = getBounds(*tPtr);
		box.leftBottom.x = min(temp.leftBottom.x, box.leftBottom.x);
		box.leftBottom.y = min(temp.leftBottom.y, box.leftBottom.y);
		box.leftBottom.z = min(temp.leftBottom.z, box.leftBottom.z);

		box.rightTop.x = max(temp.rightTop.x, box.rightTop.x);
		box.rightTop.y = max(temp.rightTop.y, box.rightTop.y);
		box.rightTop.z = max(temp.rightTop.z, box.rightTop.z);
		i++;
	}
	return box;
}

void BVH::subdivide(BVHNodeStruct* bvhNode, unsigned int* poolIndex, unsigned int* first) {
	bvhNode->leftFirst = *poolIndex;


	if (partition(bvhNode,*first)) {
		bvhNode->leftFirst = *first;
		(*first) += bvhNode->count;
		return;
	}
	*poolIndex = bvhNode->leftFirst + 2;
	subdivide(&pool[bvhNode->leftFirst], poolIndex, first);
	subdivide(&pool[bvhNode->leftFirst+1], poolIndex, first);
	bvhNode->count = 0;

}
/*
Triangle* BVH::getTriangleByIndice(unsigned int indiceIndex) {
	return *(objects + indices[indiceIndex]);
}

void BVH::setIndice(unsigned int index, unsigned int value) {
	indices[index] = value;
}*/


// POSSIBLY the worst code written by humankind
bool BVH::partition(BVHNodeStruct* bvhNode, int first) {
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

	float aLeft;
	float aRight;
	AABB aabbDefault(glm::vec3(INFINITY, INFINITY, INFINITY), glm::vec3(-INFINITY, -INFINITY, -INFINITY));

	AABB aabbLeft = aabbDefault;
	AABB aabbRight = aabbDefault;
	// 1 triangle cannot be divided since this is not a SBVH sadly enough
	if (bvhNode->count <= 1) {
		return true;
	}

	/*std::vector<int> xLeft, xRight;
	std::vector<int> yLeft, yRight;
	std::vector<int> zLeft, zRight;*/

	int* x = new int[bvhNode->count];
	int* y = new int[bvhNode->count];
	int* z = new int[bvhNode->count];

	for (int i = first; i < first + bvhNode->count; i++) {
		/*	xLeft.clear();
		xRight.clear();
		yLeft.clear();
		yRight.clear();
		zLeft.clear();
		zRight.clear();*/
		Triangle* t = getTriangleByIndice(i);
		glm::vec3 centroid = calcCentroid(t);
		int xCounter = 0, xCounterRight = bvhNode->count - 1;
		int yCounter = 0, yCounterRight = bvhNode->count - 1;
		int zCounter = 0, zCounterRight = bvhNode->count - 1;
		//float xsurfaceAreaLeft = t->getBounds().surfaceArea();
		float xsurfaceAreaLeft = 0;
		float xsurfaceAreaRight = 0;

		//float ysurfaceAreaLeft = t->getBounds().surfaceArea();
		float ysurfaceAreaLeft = 0;
		float ysurfaceAreaRight = 0;

		//float zsurfaceAreaLeft = t->getBounds().surfaceArea();
		float zsurfaceAreaLeft = 0;
		float zsurfaceAreaRight = 0;





		//not most effecient way 
		for (int j = first; j < first + bvhNode->count; j++) {
			Triangle* temp = getTriangleByIndice(j);
			glm::vec3 tempCentroid = calcCentroid(temp);
			//xsplit
			if (tempCentroid.x <= centroid.x) {
				//left
				x[xCounter] = j;
				xCounter++;
				//	xsurfaceAreaLeft += temp->getBounds().surfaceArea();
				//	xLeft.push_back(j);
			}
			else {
				//right
				x[xCounterRight] = j;
				xCounterRight--;
				//	xsurfaceAreaRight += temp->getBounds().surfaceArea();
				//	xRight.push_back(j);
			}
			//ysplit
			if (tempCentroid.y <= centroid.y) {
				//left
				y[yCounter] = j;
				yCounter++;
				//ysurfaceAreaLeft += temp->getBounds().surfaceArea();
				//yLeft.push_back(j);
			}
			else {
				//right
				y[yCounterRight] = j;
				yCounterRight--;
				//ysurfaceAreaRight += temp->getBounds().surfaceArea();
				//yRight.push_back(j);
			}
			//zsplit
			if (tempCentroid.z <= centroid.z) {
				//left
				z[zCounter] = j;
				zCounter++;
				//zsurfaceAreaLeft += temp->getBounds().surfaceArea();
				//zLeft.push_back(j);
			}
			else {
				//right
				z[zCounterRight] = j;
				zCounterRight--;
				//zsurfaceAreaRight += temp->getBounds().surfaceArea();
				//zRight.push_back(j);
			}
		}

		AABB aabbXLeft = aabbDefault;
		AABB aabbXRight = aabbDefault;
		for (int x1 = 0; x1 < xCounter; x1++) {
			Triangle* temp = getTriangleByIndice(x[x1]);
			maxBound(&aabbXLeft, &getBounds(*temp));
		}
		for (int x1 = xCounterRight + 1; x1 < bvhNode->count; x1++) {
			Triangle* temp = getTriangleByIndice(x[x1]);
			maxBound(&aabbXRight, &getBounds(*temp));
		}

		AABB aabbYLeft = aabbDefault;
		AABB aabbYRight = aabbDefault;
		for (int y1 = 0; y1 < yCounter; y1++) {
			Triangle* temp =getTriangleByIndice(y[y1]);
			maxBound(&aabbYLeft, &getBounds(*temp));
		}
		for (int y1 = yCounterRight + 1; y1 <  bvhNode->count; y1++) {
			Triangle* temp = getTriangleByIndice(y[y1]);
			maxBound(&aabbYRight, &getBounds(*temp));
		}

		AABB aabbZLeft = aabbDefault;
		AABB aabbZRight = aabbDefault;
		for (int z1 = 0; z1 < zCounter; z1++) {
			Triangle* temp = getTriangleByIndice(z[z1]);
			maxBound(&aabbZLeft, &getBounds(*temp));
		}
		for (int z1 = zCounterRight + 1; z1 <  bvhNode->count; z1++) {
			Triangle* temp = getTriangleByIndice(z[z1]);
			maxBound(&aabbZRight, &getBounds(*temp));
		}

		//float xDifference = abs(xsurfaceAreaLeft - xsurfaceAreaRight);
		//float yDifference = abs(ysurfaceAreaLeft - ysurfaceAreaRight);
		//float zDifference = abs(zsurfaceAreaLeft - zsurfaceAreaRight);
		float xSALeft = surfaceArea(aabbXLeft);
		float xSARight = surfaceArea(aabbXRight);
		float ySALeft = surfaceArea(aabbYLeft);
		float ySARight = surfaceArea(aabbYRight);
		float zSALeft = surfaceArea(aabbZLeft);
		float zSARight = surfaceArea(aabbZRight);

		float xSADifference = abs(xSALeft - xSARight);
		float ySADifference = abs(ySALeft - ySARight);
		float zSADifference = abs(zSALeft - zSARight);

		if (xSADifference < lowestDifference) {
			lowestDifference = xSADifference;
			aLeft = xSALeft;
			aRight = xSARight;
			aabbLeft = aabbXLeft;
			aabbRight = aabbXRight;

			xAxis = true;
			yAxis = false;
			zAxis = false;

			bestCentroid = centroid;
			bestLeftCount = xCounter;
		}
		if (ySADifference < lowestDifference) {
			lowestDifference = ySADifference;
			aLeft = ySALeft;
			aRight = ySARight;
			aabbLeft = aabbYLeft;
			aabbRight = aabbYRight;
			xAxis = false;
			yAxis = true;
			zAxis = false;

			bestCentroid = centroid;
			bestLeftCount = yCounter;
		}
		if (zSADifference < lowestDifference) {
			lowestDifference = zSADifference;
			aLeft = zSALeft;
			aRight = zSARight;
			aabbLeft = aabbZLeft;
			aabbRight = aabbZRight;
			xAxis = false;
			yAxis = false;
			zAxis = true;

			bestCentroid = centroid;
			bestLeftCount = zCounter;
		}
		/*
		if (xDifference < lowestDifference) {
		lowestDifference = xDifference;
		bestCentroid = centroid;
		bestLeftCount = xCounter;
		xAxis = true;
		yAxis = false;
		zAxis = false;//y false and z false
		aLeft = xsurfaceAreaLeft;
		aRight = xsurfaceAreaRight;
		}
		if (yDifference < lowestDifference) {
		lowestDifference = yDifference;
		bestCentroid = centroid;
		bestLeftCount = yCounter;
		xAxis = false;
		yAxis = true;
		zAxis = false;
		aLeft = ysurfaceAreaLeft;
		aRight = ysurfaceAreaRight;
		}
		if (zDifference < lowestDifference) {
		lowestDifference = zDifference;
		bestCentroid = centroid;
		bestLeftCount = zCounter;
		xAxis = false;
		yAxis = false;
		zAxis = true;
		aLeft = zsurfaceAreaLeft;
		aRight = zsurfaceAreaRight;
		}
		//y and z aswell*/
	}
	delete[] x, y, z;

	//should we split?
	glm::vec3 leftBottom = glm::vec3(bvhNode->leftBottom.x, bvhNode->leftBottom.y, bvhNode->leftBottom.z);
	glm::vec3 rightTop = glm::vec3(bvhNode->rightTop.x, bvhNode->rightTop.y, bvhNode->rightTop.z);
	AABB* bounds = new AABB(leftBottom, rightTop);
	float test = surfaceArea(*bounds);
	if ((aLeft * bestLeftCount + aRight * (bvhNode->count - bestLeftCount)) >= surfaceArea(*bounds) * bvhNode->count) {
		// we shouldnt
		return true;
	}


	//Recalculate for some reason well mostly because it needs to change and I am lazy
	//might actually interesting to keep it like this since bounds will only be calculated once than
	//int indicesMiddle = first + bestLeftCount - 1;
	//setIndice(bestIndice, indicesMiddle);
	//left->first = bestIndice;
	int leftIndice = 0;// first;
	int rightIndice = bvhNode->count - 1; // first + count - 1;
								 //for swapping
								 //int* indices = getIndices();
								 //AABB aabbLeft(glm::vec3(INFINITY, INFINITY, INFINITY), glm::vec3(-INFINITY, -INFINITY, -INFINITY));
								 //AABB aabbRight(glm::vec3(INFINITY, INFINITY, INFINITY), glm::vec3(-INFINITY, -INFINITY, -INFINITY));
	unsigned int* backup = new unsigned int[bvhNode->count];
	for (int i = 0; i < bvhNode->count; i++) {
		backup[i] = indices[first + i];
	}

	for (int i = first; i < first + bvhNode->count; i++) {
		//if (i != bestIndice) {
		Triangle* temp = getTriangleByIndice(i);
		glm::vec3 tempCentroid = calcCentroid(temp);
		//xsplit
		bool left = false;
		if (xAxis) {
			left = tempCentroid.x <= bestCentroid.x;
		}
		if (yAxis) {
			left = tempCentroid.y <= bestCentroid.y;
		}
		if (zAxis) {
			left = tempCentroid.z <= bestCentroid.z;
		}
		if (left) {
			//left
			//swapping is an issue
			//bvh->setIndice(leftIndice, i);
			backup[leftIndice] = indices[i];
			leftIndice++;
			//maxBound(&aabbLeft, &temp->getBounds());
		}
		else {
			//right
			//bvh->setIndice(rightIndice, i);
			backup[rightIndice] = indices[i];
			rightIndice--;
			//maxBound(&aabbRight, &temp->getBounds());
		}
		//}
	}
	//overwrite values;
	for (int i = 0; i < bvhNode->count; i++) {
		indices[first + i] = backup[i];
	}
	//not sure if required since local variable but yea 
	delete[] backup;

	//bvh->pool[left].first = first;
	pool[bvhNode->leftFirst].count = bestLeftCount;
	pool[bvhNode->leftFirst].leftBottom = { aabbLeft.leftBottom.x, aabbLeft.leftBottom.y, aabbLeft.leftBottom.z };
	pool[bvhNode->leftFirst].rightTop = { aabbLeft.rightTop.x, aabbLeft.rightTop.y, aabbLeft.rightTop.z };
	//bvh->pool[left+1].first = first+rightIndice+1; //first+count-bestLeftCount;
	pool[bvhNode->leftFirst + 1].count = bvhNode->count - bestLeftCount;
	pool[bvhNode->leftFirst +1 ].leftBottom = { aabbRight.leftBottom.x, aabbRight.leftBottom.y, aabbRight.leftBottom.z };
	pool[bvhNode->leftFirst + 1].rightTop = { aabbRight.rightTop.x, aabbRight.rightTop.y, aabbRight.rightTop.z };

	return false;
}

void BVH::maxBound(AABB* aabb, const AABB* check) {
	aabb->leftBottom.x = min(check->leftBottom.x, aabb->leftBottom.x);
	aabb->leftBottom.y = min(check->leftBottom.y, aabb->leftBottom.y);
	aabb->leftBottom.z = min(check->leftBottom.z, aabb->leftBottom.z);

	aabb->rightTop.x = max(check->rightTop.x, aabb->rightTop.x);
	aabb->rightTop.y = max(check->rightTop.y, aabb->rightTop.y);
	aabb->rightTop.z = max(check->rightTop.z, aabb->rightTop.z);
}

float BVH::surfaceArea(AABB aabb) {

	//0 is kind of an issue 
	/*if (result.x == 0) {
	result.x = 0.1;
	}
	if (result.y == 0) {
	result.y = 0.1;
	}
	if (result.z == 0) {
	result.z = 0.1;
	}*/
	//return abs(result.x*result.y*result.z);
	// 2 * SA(xy) + 2 * SA(xz) + 2 * SA(yz)
	// 2 * (SA(XY) + SA(XZ) + SA(YZ)
	glm::vec3 result = aabb.rightTop - aabb.leftBottom;
	return 2.f * (result.x*result.y + result.x*result.z + result.y*result.z);

}

glm::vec3 BVH::calcCentroid(Triangle* t) {
	float x = t->v1.x + t->v2.x + t->v3.x / 3.0f;
	float y = t->v1.y + t->v2.y + t->v3.y / 3.0f;
	float z = t->v1.z + t->v2.z + t->v3.z / 3.0f;
	return glm::vec3(x, y, z);
	//(t->v1 + t->v2 + t->v3) / 3.0f;
}

Triangle* BVH::getTriangleByIndice(unsigned int indiceIndex) {
	return (objects + indices[indiceIndex]);
}