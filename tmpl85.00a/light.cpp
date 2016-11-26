#include "template.h"
#include "light.h"


Light::Light(glm::vec3 position, glm::vec3 direction, float lightIntensity, Tmpl8::Pixel color) :
	Placeable(position, direction), lightIntensity(lightIntensity), color(color) {


}