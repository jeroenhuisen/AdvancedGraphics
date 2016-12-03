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
	Material(Color color, float reflectioness = 0, float glossiness = 0);
	Color getColor() { return color; };
	float getReflectioness();
	float getGlossiness();
};