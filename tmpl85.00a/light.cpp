#include "template.h"
#include "light.h"


Light::Light(const glm::vec3 position, const glm::vec3 direction, const float lightIntensity, const Color color, const float attenuationConstant, const float attenuationLinear, const float attenuationQuadratic) :
	Placeable(position, direction), lightIntensity(lightIntensity), color(color), attenuationConstant(attenuationConstant), attenuationLinear(attenuationLinear), attenuationQuadratic(attenuationQuadratic){


}

Color Light::getColor() {
	return color;
}