#pragma once
#include "template.h"
#include "object.h"


class Triangle : public Object {
private:
	glm::vec3 v1, v2, v3;
	float EPSILON = 0.000001;
public:
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material* material);
	glm::vec3 intersection(Ray r, float* distance);
};