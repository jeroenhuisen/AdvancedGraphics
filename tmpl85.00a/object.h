#pragma once
#include "template.h"

#include "ray.h"

class Object {
protected:
	glm::vec3 position;
	glm::vec3 direction;
public:
	Object(glm::vec3 position, glm::vec3 direction);
	glm::vec3 getPosition();
	glm::vec3 getDirection();

	virtual glm::vec3 intersection(Ray r) = 0;
};