#pragma once
#include "template.h"


class Material {
private:
	Tmpl8::Pixel color;
	 // just for now
public:
	Material(Tmpl8::Pixel color);
	Tmpl8::Pixel getColor() { return color; };
};