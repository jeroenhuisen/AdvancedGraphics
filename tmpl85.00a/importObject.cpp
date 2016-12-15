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

AABB ImportObject::getBounds() {
	//not most efficient calculating everytime but object can now move?
	AABB box = AABB(glm::vec3(INFINITE, INFINITE, INFINITE), glm::vec3(-INFINITE, -INFINITE, -INFINITE));
	for (Triangle* triangle : triangles) {
		AABB temp = triangle->getBounds();
		box.leftBottom.x = min(temp.leftBottom.x, box.leftBottom.x);
		box.leftBottom.y = min(temp.leftBottom.y, box.leftBottom.y);
		box.leftBottom.z = min(temp.leftBottom.z, box.leftBottom.z);

		box.rightTop.x = min(temp.rightTop.x, box.rightTop.x);
		box.rightTop.y = min(temp.rightTop.y, box.rightTop.y);
		box.rightTop.z = min(temp.rightTop.z, box.rightTop.z);
	}
	return box;
}