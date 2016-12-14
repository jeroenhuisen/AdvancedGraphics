#include "template.h"

#include "pointlight.h"

PointLight::PointLight(const glm::vec3 position, const float lightIntensity, Color color, const float attenuationConstant, const float attenuationLinear, const float attenuationQuadratic) :
	Light(position, glm::vec3(0, 0, 0), lightIntensity, color, attenuationConstant, attenuationLinear, attenuationQuadratic) {

}

float PointLight::calculateStrength(const float distance) {
	return lightIntensity / (attenuationConstant + attenuationLinear*distance + attenuationQuadratic*distance*distance);
}