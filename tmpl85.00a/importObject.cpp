#include "template.h"
#include "ImportObject.h"

ImportObject::ImportObject(const glm::vec3 position, const glm::vec3 direction, Material* material, Triangle* triangles, int amountOfTriangles) :
	Object(position, direction, material), triangles(triangles), amount(amountOfTriangles) {

	move(position);
}

void ImportObject::move(const glm::vec3 newPos) {
	for (Triangle* tPtr = triangles; tPtr < triangles+amount; tPtr++){
		tPtr->v1 += newPos;
		tPtr->v2 += newPos;
		tPtr->v3 += newPos;

		tPtr->precalculate();
	}
}
glm::vec3 ImportObject::intersection(const Ray r, float* distance) {
	glm::vec3 intersection;
	for (Triangle* tPtr = triangles; tPtr < triangles + amount; tPtr++) {
		float temp = *distance;
		glm::vec3 tempIn = tPtr->intersection(r, distance);
		if (temp > *distance) {
			intersection = tempIn;
		}
	}
	return intersection;
}