#pragma once
#include "template.h"
#include "light.h"

class PointLight : public Light {
public:
	PointLight(const glm::vec3 position, const float lightIntensity, const Color color, const float attenuationConstant, const float attenuationLinear, const float attenuationQuadratic);
	float calculateStrength(const float distance);
};