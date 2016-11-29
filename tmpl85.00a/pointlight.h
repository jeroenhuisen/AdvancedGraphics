#pragma once
#include "template.h"
#include "light.h"

class PointLight : public Light {
public:
	PointLight(glm::vec3 position, float lightIntensity, Color color, float attenuationConstant, float attenuationLinear, float attenuationQuadratic);
	float calculateStrength(float distance);
};