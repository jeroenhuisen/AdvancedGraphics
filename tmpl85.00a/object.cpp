#include "object.h"
#include "template.h"

Object::Object(const glm::vec3 position, const glm::vec3 direction, Material* material):
	Placeable(position, direction), material(material){
//add this{

}

Object::~Object() {
	delete material;
}

Material* Object::getMaterial() {
	return material;
}