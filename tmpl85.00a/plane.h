#pragma once
#include "template.h"
#include "object.h"
#include <iostream>


class Plane : public Object {
private:

public:
	Plane(const glm::vec3 position, const glm::vec3 direction, Material* material);
	glm::vec3 intersection(Ray r, float* distance);
};