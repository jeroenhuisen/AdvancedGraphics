#pragma once
#include "template.h"

#include "object.h"

class Primitive : public Object{
public:
	// Please change the values this is only here for simplification/testing
	Primitive() {}
	Primitive(const glm::vec3 position, const glm::vec3 direction, Material* material);
	virtual AABB getBounds() = 0;
};