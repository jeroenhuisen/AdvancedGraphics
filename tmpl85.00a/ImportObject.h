#pragma once
#include "object.h"

class ImportObject : public Object {
private:
	//std::vector<Triangle*> triangles;
public:
	//std::vector<Triangle*> triangles;
	Triangle* triangles;
	int amount;

	// Please change the values this is only here for simplification/testing
	ImportObject() {}
	ImportObject(const glm::vec3 position, const glm::vec3 direction, Material* material, Triangle* triangles, int amountOfTriangles);
	glm::vec3 intersection(const Ray r, float* distance);

	void move(const glm::vec3 newPos);
};