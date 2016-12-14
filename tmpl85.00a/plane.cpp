#include "template.h"
#include "plane.h"

Plane::Plane(const vec3 position, const vec3 direction, Material* material) :
	Object(position, direction, material) {

}

glm::vec3 Plane::intersection(Ray r, float* distance) {
	*distance = glm::dot(position - r.origin, direction) / glm::dot(r.direction, direction);
	return direction;
}

	