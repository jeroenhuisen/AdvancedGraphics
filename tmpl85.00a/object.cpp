#include "object.h" 
#include "template.h"


Object::Object(glm::vec3 position, glm::vec3 direction) :
	position(position), direction(direction) {

}

glm::vec3 Object::getPosition() {
	return position;
}

glm::vec3 Object::getDirection() {
	return direction;
}