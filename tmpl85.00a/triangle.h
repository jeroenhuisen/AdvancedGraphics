#pragma once
#include "template.h"
#include "primitive.h"


class Triangle : public Primitive {
private:
	
	const float EPSILON = 0.000001;
	glm::vec3 e1, e2;
	void updateBounds();
public:
	// Please change the values this is only here for simplification/testing
	Triangle() {}
	Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3, Material* material);
	Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3, const glm::vec3 n1, const glm::vec3 n2, const glm::vec3 n3, Material* material);
	glm::vec3 intersection(const Ray r, float* distance);

	glm::vec3 v1, v2, v3;
	glm::vec3 centroid;

	void precalculate();
	AABB getBounds();

	AABB boundingBox;
};