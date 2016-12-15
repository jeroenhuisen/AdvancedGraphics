#include "template.h"
#include "ImportObject.h"

ImportObject::ImportObject(const glm::vec3 position, const glm::vec3 direction, Material* material, std::vector<Triangle*> triangles) :
	Object(position, direction, material), triangles(triangles) {

	for (Triangle* triangle : this->triangles) {
		triangle->v1 += position;
		triangle->v2 += position;
		triangle->v3 += position;
	}
}

glm::vec3 ImportObject::intersection(const Ray r, float* distance) {
	glm::vec3 intersection;
	for (Triangle* triangle : triangles) {
		float temp = *distance;
		glm::vec3 tempIn = triangle->intersection(r, distance);
		if (temp > *distance) {
			intersection = tempIn;
		}
	}
	return intersection;
}