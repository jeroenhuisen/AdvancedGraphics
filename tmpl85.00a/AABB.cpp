#include "template.h"
#include "AABB.h"

AABB::AABB(const glm::vec3 leftBottom, const glm::vec3 rightTop):
	leftBottom(leftBottom), rightTop(rightTop){

}

float AABB::surfaceArea() {
	glm::vec3 result = rightTop - leftBottom;
	return result.x*result.y*result.z;
}