#include "template.h"

#include "pointlight.h"

PointLight::PointLight(glm::vec3 position, float lightIntensity, Tmpl8::Pixel color, float attenuationConstant, float attenuationLinear, float attenuationQuadratic) :
	Light(position, glm::vec3(0, 0, 0), lightIntensity, color, attenuationConstant, attenuationLinear, attenuationQuadratic) {

}

float PointLight::calculateStrength(float distance) {
	return lightIntensity / (attenuationConstant + attenuationLinear*distance + attenuationQuadratic*distance*distance);
}