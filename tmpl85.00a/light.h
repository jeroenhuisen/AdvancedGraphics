#pragma once
#include "template.h"
#include "object.h"

class Light : public Placeable {
protected:
	float lightIntensity;
	float attenuationConstant, attenuationLinear, attenuationQuadratic;
	Tmpl8::Pixel color;
public:
	Light(glm::vec3 position, glm::vec3 direction, float lightIntensity, Tmpl8::Pixel color, float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
	virtual float calculateStrength(float distance) = 0;
};