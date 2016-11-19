#pragma once
#include "template.h"

class Object {
protected:
	glm::vec3 position;
	glm::vec3 direction;
public:
	Object(glm::vec3 position, glm::vec3 direction);
	glm::vec3 getPosition();
	glm::vec3 getDirection();
};