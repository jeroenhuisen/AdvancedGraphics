#pragma once

#include "template.h"

class Ray {
private:
	glm::vec3 origin;
	glm::vec3 direction;
public:
	Ray(glm::vec3 origin, glm::vec3 direction);
};