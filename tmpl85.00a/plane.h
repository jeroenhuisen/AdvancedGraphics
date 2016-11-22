#pragma once
#include "object.h"
#include "template.h"


class Plane : public Object {
private:
	float width, height;
public:
	Plane(glm::vec3 position, glm::vec3 direction, float width, float height);
	glm::vec3 intersection(Ray r) {
		/*position;
		r.getOrigin() + r.getDirection();
		direction*/

		// probably most ineffecient way
		float value = glm::dot(position - r.getOrigin(), direction) / glm::dot(r.getDirection(), direction);

		// Doesnt check the width and height....
		//return r.getDirection() * value + r.getOrigin();
		glm::vec3 result = r.getDirection() * value + r.getOrigin();
		//glm::vec3 max = position + direction * glm::vec3(width, height, 0);
		//min is position;
		if (position.x <= result.x && result.x <= width	&&
			position.z <= result.z && result.z <= height ){ //&&
			///position.z >= result.z && max.x <= result.z) {
			
				return result;
		}
		else {
			return glm::vec3();
		}


		/*if (glm::dot(result - position, direction) == 0) {
			return result;
		}*/

	}
};