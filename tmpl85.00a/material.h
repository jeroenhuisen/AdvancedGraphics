#pragma once
#include "template.h"
#include "color.h"


class Material {
private:
	//Color color;
	 // just for now
	float reflectioness;
	float fresnellValueStuff;//fix that I guess
public:
	Color color;
	Material(Color color, float reflectioness = 0);
	Color getColor() { return color; };
	float getReflectioness();
};