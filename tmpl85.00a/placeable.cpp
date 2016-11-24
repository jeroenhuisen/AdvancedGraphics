#include "placeable.h" 
#include "template.h"


Placeable::Placeable(glm::vec3 pos, glm::vec3 dir) :
	position(pos), direction(dir) {

}

glm::vec3 Placeable::getPosition() {
	return position;
}

glm::vec3 Placeable::getDirection() {
	return direction;
}