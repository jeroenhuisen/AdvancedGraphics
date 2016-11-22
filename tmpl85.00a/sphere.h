#pragma once
#include "template.h"

#include "primitive.h"


class Sphere : public Primitive{
private:
	float radius;
public:
	Sphere(glm::vec3 position, float radius, Material* material);
	// implement
	glm::vec3 intersection(Ray r) {
		return glm::vec3();
	}
};