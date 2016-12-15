#pragma once
#include "template.h"

#include "object.h"

class Primitive : public Object{
public:
	Primitive(const glm::vec3 position, const glm::vec3 direction, Material* material);
	virtual AABB getBounds() = 0;
};