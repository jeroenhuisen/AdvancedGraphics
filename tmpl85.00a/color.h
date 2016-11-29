#pragma once
#include "template.h"


class Color {
public:
	float r;
	float g;
	float b;

	Color(float r, float g, float b);
	Tmpl8::Pixel getRGB();
};