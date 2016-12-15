#pragma once
#include "object.h"

class ImportObject : public Object {
private:
	std::vector<Triangle*> triangles;
public:
	ImportObject(const glm::vec3 position, const glm::vec3 direction, Material* material, std::vector<Triangle*> triangles);
	glm::vec3 intersection(const Ray r, float* distance);
	AABB getBounds();
};