#include "template.h"
#include "triangle.h"


Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, Material* material) :
	Object(v1, glm::normalize(glm::cross((v2-v1),(v3-v1))), material), v1(v1), v2(v2), v3(v3){

}

glm::vec3 Triangle::intersection(Ray r, float* distance) {
	glm::vec3 e1 = v2 - v1;
	glm::vec3 e2 = v3 - v1;
	glm::vec3 P = glm::cross(r.direction, e2);
	float det = glm::dot(e1, P);
	if ((det > -EPSILON) && (det < EPSILON)) {
		return glm::vec3(); // Ray is either parallel to or inside the triangle
	}
	float inv_det = 1 / det;
	glm::vec3 T = r.origin - v1;
	float u = glm::dot(T, P) * inv_det;
	if ((u < 0) || (u > 1)) {
		return glm::vec3(); // Intersection lies outside of the triangle
	}
	glm::vec3 Q = glm::cross(T, e1);
	float v = dot(r.direction, Q) * inv_det;
	if ((v < 0) || (u + v > 1)) {
		return glm::vec3(); // Again, intersection outside of the triangle
	}
	float t = glm::dot(e2, Q) * inv_det;
	if (t > 0) {
		*distance = glm::min(*distance, t);
	}
	return direction; // Normalised normal of the triangle
}