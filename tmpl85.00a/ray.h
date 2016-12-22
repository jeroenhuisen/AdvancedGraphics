#pragma once

#include "template.h"

class Ray {
private:
	/*glm::vec3 origin;
	glm::vec3 direction;*/
public:
	Ray(const glm::vec3 origin, const glm::vec3 direction);
	/*glm::vec3 getOrigin();
	glm::vec3 getDirection();*/
	int bvhHit = 0;
	glm::vec3 origin;
	glm::vec3 direction;
};