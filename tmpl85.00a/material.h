#pragma once
#include "template.h"
#include "color.h"


class Material {
private:
	//Color color;
	 // just for now
	float reflectioness;
	float glossiness;
public:
	Color color;
	Material(const Color color, const float reflectioness = 0, const float glossiness = 0);
	Color getColor() { return color; };
	float getReflectioness();
	float getGlossiness();
};