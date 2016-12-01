#include "template.h"
#include "sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, Material* material) :
	Object(position, vec3(0, 0, 0), material), radius(radius*radius) {

}

glm::vec3 Sphere::intersection(Ray r, float* distance) {
	glm::vec3 c = position - r.getOrigin();
	float t = glm::dot(c, r.getDirection());
	vec3 q = c - t * r.getDirection();
	float p2 = glm::dot(q, q);
	if ((p2 > radius) && (t > 0)) {
		return glm::vec3();
	}
	*distance = t - glm::sqrt(radius - p2);//glm::length(c) - radius;
	
	return glm::normalize(r.getOrigin() + *distance * r.getDirection() - c);//normal
}