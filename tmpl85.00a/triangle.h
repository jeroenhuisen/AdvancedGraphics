#pragma once
#include "template.h"
#include "object.h"


class Triangle : public Object {
private:
	
	const float EPSILON = 0.000001;
public:
	Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3, Material* material);
	Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3, const glm::vec3 n1, const glm::vec3 n2, const glm::vec3 n3, Material* material);
	glm::vec3 intersection(const Ray r, float* distance);
	glm::vec3 v1, v2, v3;

	AABB getBounds();
};