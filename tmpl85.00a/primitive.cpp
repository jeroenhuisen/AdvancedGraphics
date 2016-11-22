#include "template.h"

#include "primitive.h"

Primitive::Primitive(vec3 position, vec3 direction, Material* material) :
	Object(position, direction), material(material) {
};