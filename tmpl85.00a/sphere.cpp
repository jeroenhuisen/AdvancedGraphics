#include "template.h"
#include "sphere.h"

Sphere::Sphere(const glm::vec3 position, const float radius, Material* material) :
	Primitive(position, vec3(0, 0, 0), material), radius(radius*radius) {

}

glm::vec3 Sphere::intersection(const Ray r, float* distance) {
	glm::vec3 c = position - r.origin;
	glm::vec3 dir = r.direction;
	float t = glm::dot(c, dir);
	vec3 q = c - t * dir;

	float p2 = glm::dot(q, q);
	if ((p2 > radius) && (t > 0)) {
		return glm::vec3();
	}
	*distance = t - glm::sqrt(radius - p2);
	
	return glm::normalize(r.origin + *distance * dir - position);//normal (intersection - position)
}

AABB Sphere::getBounds() {
	float rad = radius*0.5;
	return AABB(position - rad, position + rad);//glm::vec3(position.x - rad, position.y - rad, position))
}