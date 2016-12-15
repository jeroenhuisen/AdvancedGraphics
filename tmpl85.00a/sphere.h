#pragma once
#include "template.h"

#include "object.h"


class Sphere : public Object{
private:
	float radius;
public:
	Sphere(const glm::vec3 position, const float radius, Material* material);
	// implement
	glm::vec3 intersection(const Ray r, float* distance);
	AABB getBounds();
};