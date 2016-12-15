#include "template.h"
#include "primitive.h"

Primitive::Primitive(const glm::vec3 position, const glm::vec3 direction, Material* material) :
	Object(position, direction, material) {

}