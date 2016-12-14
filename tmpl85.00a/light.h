#pragma once
#include "template.h"
#include "object.h"

class Light : public Placeable {
protected:
	float lightIntensity;
	float attenuationConstant, attenuationLinear, attenuationQuadratic;
	Color color;
public:
	Light(const glm::vec3 position, const glm::vec3 direction, const float lightIntensity, const Color color, const float attenuationConstant, const float attenuationLinear, const float attenuationQuadratic);
	virtual float calculateStrength(float distance) = 0;

	Color getColor();
};