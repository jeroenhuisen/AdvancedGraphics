#include "template.h"
#include "plane.h"

Plane::Plane(vec3 position, vec3 direction, float width, float height, Material* material) :
	Object(position, direction, material), width(width), height(height) {

}

glm::vec3 Plane::intersection(Ray r, float* distance) {
	/*position;
	r.getOrigin() + r.getDirection();
	direction*/

	// probably most ineffecient way
	float value = glm::dot(position - r.getOrigin(), direction) / glm::dot(r.getDirection(), direction);

	if (value <= 0) {
		*distance = INFINITE;
		return glm::vec3();
	}

	// Doesnt check the width and height....
	//return r.getDirection() * value + r.getOrigin();
	glm::vec3 result = r.getDirection() * value + r.getOrigin();
	//glm::vec3 max = position + direction * glm::vec3(width, height, 0);
	//min is position;
	// if statement for y = 1 direction
	float width2 = width / 2;
	float height2 = height / 2;
	/*if ((position.x + zAxisLocal90C * direction *  width2) <= r.getDirection().x && r.getDirection().x <= (position.x + zAxisLocal90 * direction *  width2) &&
		(position.z + xAxisLocal90C * direction *  height2) <= r.getDirection().z && r.getDirection().z <= (position.z + xAxisLocal90 * direction *  height2)) {*/
	vec3 min = position + zAxisLocal90C * direction *  width2  + xAxisLocal90C * direction *  height2;
	vec3 max = position + zAxisLocal90 * direction *  width2  + xAxisLocal90 * direction *  height2;
	if (min.x > max.x) {
		float temp = max.x;
		max.x = min.x;
		min.x = temp;
	}
	if (min.y > max.y) {
		float temp = max.y;
		max.y = min.y;
		min.y = temp;
	}
	if (min.z > max.z) {
		float temp = max.z;
		max.z = min.z;
		min.z = temp;
	}
	/*if( min.x <= result.x && result.x <= max.x &&
		min.y <= result.y && result.y <= max.y &&
		min.z <= result.z && result.z <= max.z){*/
		//if (position.x <= result.x && result.x <= position.x + width &&
		//	position.z <= result.z && result.z <= position.z + height ){ //&&
		///position.z >= result.z && max.x <= result.z) {
		*distance = glm::length(r.getOrigin() - result);// used for determining the distance I guess
		return result;
	/*}
	else {
		*distance = INFINITE;
		return glm::vec3();
	}


	/*if (glm::dot(result - position, direction) == 0) {
	return result;
	}*/

}