#pragma once
#include "template.h"

#include "object.h"


class Sphere : public Object{
private:
	float radius;
public:
	Sphere(glm::vec3 position, float radius, Material* material);
	// implement
	glm::vec3 intersection(Ray r, float* distance) {
		return glm::vec3();
	}
};