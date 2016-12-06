#include "object.h"
#include "template.h"

Object::Object(glm::vec3 position, glm::vec3 direction, Material* material):
	Placeable(position, direction), material(material){
//add this{

}

Object::~Object() {
	delete material;
}

Material* Object::getMaterial() {
	return material;
}