#include "template.h"
#include "sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, Material* material) :
	Object(position, vec3(0, 0, 0), material), radius(radius*radius) {

}

glm::vec3 Sphere::intersection(Ray r, float* distance) {
	glm::vec3 c = position - r.getOrigin();
	glm::vec3 dir = r.getDirection();
	float t = glm::dot(c, dir);
	vec3 q = c - t * dir;

	float p2 = glm::dot(q, q);
	if ((p2 > radius) && (t > 0)) {
		return glm::vec3();
	}
	*distance = t - glm::sqrt(radius - p2);//glm::length(c) - radius;
	
	return glm::normalize(r.getOrigin() + *distance * dir - c);//normal
	/*glm::vec3 bs = r.getOrigin() - position;
	return glm::normalize(bs);*/
}