#pragma once
#include "template.h"
#include "ray.h"
#include "placeable.h"
#include "material.h"

class Object : public Placeable{
protected:
	Material* material; //could be a pointer if you want to change the the material externally with risk of changing material of multiple objects at the same time. I guess we do that...
public:
	Object(const glm::vec3 position, const glm::vec3 direction, Material* material);
	~Object();
	Material* getMaterial();
	virtual glm::vec3 intersection(Ray r, float* distance) = 0;
};