#include "template.h"
#include "sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, Material* material) :
	Object(position, vec3(0, 0, 0), material), radius(radius) {

}