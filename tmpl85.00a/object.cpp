#include "object.h" 
#include "template.h"


Object::Object(glm::vec3 pos, glm::vec3 dir) :
	position(pos), direction(dir) {

}

glm::vec3 Object::getPosition() {
	return position;
}

glm::vec3 Object::getDirection() {
	return direction;
}