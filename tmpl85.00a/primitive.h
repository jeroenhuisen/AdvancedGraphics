#pragma once
#include "template.h"

#include "object.h"
#include "material.h"

class Primitive : public Object {
protected:
	Material* material;

public:
	Primitive(glm::vec3 position, glm::vec3 direction, Material* material);
	//virtual glm::vec3 intersection(Ray r);
};
