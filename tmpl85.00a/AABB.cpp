#include "template.h"
#include "AABB.h"

AABB::AABB(const glm::vec3 leftBottom, const glm::vec3 rightTop):
	leftBottom(leftBottom), rightTop(rightTop){

}

float AABB::surfaceArea() {
	glm::vec3 result = rightTop - leftBottom;
	//0 is kind of an issue 
	if (result.x == 0) {
		result.x = 0.1;
	}
	if (result.y == 0) {
		result.y = 0.1;
	}
	if (result.z == 0) {
		result.z = 0.1;
	}
	return abs(result.x*result.y*result.z);
}