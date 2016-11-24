#include "object.h"
#include "template.h"

Object::Object(glm::vec3 position, glm::vec3 direction, Material* material):
	Placeable(position, direction), material(material){
//add this{

}

Material* Object::getMaterial() {
	return material;
}