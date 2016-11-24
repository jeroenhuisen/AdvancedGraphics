#include "template.h"
#include "plane.h"

Plane::Plane(vec3 position, vec3 direction, float width, float height, Material* material) :
	Object(position, direction, material), width(width), height(height) {

}

/*glm::vec3 Object::intersection(Ray r) {


	// probably most ineffecient way
	float value = glm::dot(position - r.getOrigin(), direction) / glm::dot(r.getDirection(), direction);

	// Doesnt check the width and height....
	//return r.getDirection() * value + r.getOrigin();
	position + direction * glm::vec3(Plane::width, Plane::height, 1); // 

	
}*/