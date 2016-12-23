#include "template.h"
#include "triangle.h"


Triangle::Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3, Material* material) :
	Primitive(v1, glm::normalize(glm::cross((v2-v1),(v3-v1))), material), v1(v1), v2(v2), v3(v3) {
	glm::vec3 test = (v1 + v2 + v3) / 3.0f;
	centroid = (v1 + v2 + v3) / 3.0f;

}

Triangle::Triangle(const glm::vec3 v1, const glm::vec3 v2, const glm::vec3 v3, const glm::vec3 n1, const glm::vec3 n2, const glm::vec3 n3, Material* material) :
	Primitive(v1, glm::normalize(n1 + n2 + n3), material), v1(v1), v2(v2), v3(v3) {
	centroid = (v1 + v2 + v3) / 3.0f;

}

glm::vec3 Triangle::intersection(const Ray r, float* distance) {
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

void Triangle::updateBounds() {
	float xMin = min(v1.x, v2.x);
	xMin = min(xMin, v3.x);
	float yMin = min(v1.y, v2.y);
	yMin = min(yMin, v3.y);
	float zMin = min(v1.z, v2.z);
	zMin = min(zMin, v3.z);

	float xMax = max(v1.x, v2.x);
	xMax = max(xMax, v3.x);
	float yMax = max(v1.y, v2.y);
	yMax = max(yMin, v3.y);
	float zMax = max(v1.z, v2.z);
	zMax = max(zMax, v3.z);

	/*float xMin = v1.x, yMin = v1.y, zMin = v1.z;
	float xMax = v1.x, yMax = v1.y, zMax = v1.z;

	if (v2.x > xMin) {
		xMax = v2.x;
	}
	else { // == aswell for no real reason
		xMin = v2.x;
	}
	if (v2.y > yMin) {
		yMax = v2.y;
	}
	else { // == aswell for no real reason
		yMin = v2.y;
	}
	if (v2.z > zMin) {
		zMax = v2.z;
	}
	else { // == aswell for no real reason
		zMin = v2.z;
	}


	if (v3.x > xMin) {
		xMax = v3.x;
	}
	else { // == aswell for no real reason
		xMin = v3.x;
	}
	if (v3.y > yMin) {
		yMax = v3.y;
	}
	else { // == aswell for no real reason
		yMin = v3.y;
	}
	if (v3.z > zMin) {
		zMax = v3.z;
	}
	else { // == aswell for no real reason
		zMin = v3.z;
	}
	*/
	boundingBox = AABB(glm::vec3(xMin, yMin, zMin), glm::vec3(xMax, yMax, zMax));
}

AABB Triangle::getBounds() {
	return boundingBox;
}