#pragma once
#include "template.h"

class Camera {
private:
	glm::vec3 position;
	glm::vec3 viewingDirection;
	float screenDistance;
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 viewingDirection = glm::vec3(0.0f, 0.0f, 1.0f), float screenDistance = 1.0f);
};