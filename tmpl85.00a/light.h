#pragma once
#include "template.h"
#include "object.h"

class Light : public Placeable {
protected:
	float lightIntensity;
	float attenuationConstant, attenuationLinear, attenuationQuadratic;
	Color color;
public:
	Light(glm::vec3 position, glm::vec3 direction, float lightIntensity, Color color, float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
	virtual float calculateStrength(float distance) = 0;

	Color getColor();
};