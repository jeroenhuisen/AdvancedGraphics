#include "ray.h"
#include "template.h"

Ray::Ray(const vec3 origin, const vec3 direction) :
	origin(origin), direction(glm::normalize(direction)) {
}
/*
glm::vec3 Ray::getOrigin() {
	return origin;
}

glm::vec3 Ray::getDirection() {
	return direction;
}*/