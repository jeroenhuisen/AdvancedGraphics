#pragma once
#include "template.h"


class Color {
public:
	float r;
	float g;
	float b;

	Color(const float r, const float g, const float b);
	Tmpl8::Pixel getRGB();

	void to1();
	void to255();

	Color operator * (const float &f) { return Color(r*f, g*f, b*f); }
	Color operator + (const Color &c) { return Color(r + c.r, g + c.g, b + c.b); }
	Color& operator += (const Color &c) { r += c.r; g += c.g; b += c.b; return *this;  }
	Color operator * (const Color &c) { return Color(r*c.r, g*c.g, b*c.b); }
};

