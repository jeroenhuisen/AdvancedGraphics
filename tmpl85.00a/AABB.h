#pragma once
#include "placeable.h"

class AABB {//: public Placeable {
public:
	glm::vec3 leftBottom;
	glm::vec3 rightTop;

	AABB() {}
	AABB(const glm::vec3 leftBottom, const glm::vec3 rightTop);
};