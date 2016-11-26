#include "template.h"

#include "pointlight.h"

PointLight::PointLight(glm::vec3 position, float lightIntensity, Tmpl8::Pixel color) :
	Light(position, glm::vec3(0, 0, 0), lightIntensity, color) {

}