#pragma once
#include "template.h"
#include "object.h"
#include <iostream>


class Plane : public Object {
private:
	float width, height;
public:
	Plane(glm::vec3 position, glm::vec3 direction, float width, float height, Material* material);
	glm::vec3 intersection(Ray r, float* distance);
};