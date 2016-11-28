#include "template.h"
#include "light.h"


Light::Light(glm::vec3 position, glm::vec3 direction, float lightIntensity, Tmpl8::Pixel color, float attenuationConstant, float attenuationLinear, float attenuationQuadratic) :
	Placeable(position, direction), lightIntensity(lightIntensity), color(color), attenuationConstant(attenuationConstant), attenuationLinear(attenuationLinear), attenuationQuadratic(attenuationQuadratic){


}

Tmpl8::Pixel Light::getColor() {
	return color;
}