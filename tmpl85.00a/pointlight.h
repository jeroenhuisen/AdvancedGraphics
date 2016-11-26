#pragma once
#include "template.h"
#include "light.h"

class PointLight : public Light {
public:
	PointLight(glm::vec3 position, float lightIntensity, Tmpl8::Pixel color);
};