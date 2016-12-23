#pragma once
#include "placeable.h"

class AABB {//: public Placeable {
public:
	glm::vec3 leftBottom;
	glm::vec3 rightTop;

	AABB() {}
	AABB(const glm::vec3 leftBottom, const glm::vec3 rightTop);
	float surfaceArea();
	//http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
	bool intersects(Ray* r);
};