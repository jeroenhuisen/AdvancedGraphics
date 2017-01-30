#pragma once

struct BVHNode {
	float3 leftBottom;
	float3 rightTop;

	int leftFirst;
	int count; //amount of triangles
	// doesn't have to be here but I am lazyy
	//Triangle* triangle; //nvm
};