#pragma once
#include "template.h"

class Placeable {
protected:
//	glm::vec3 position;
//	glm::vec3 direction;
public:
	Placeable(const glm::vec3 position, const glm::vec3 direction);
	//glm::vec3 getPosition();
	//glm::vec3 getDirection();

	glm::vec3 position;
	glm::vec3 direction;
};