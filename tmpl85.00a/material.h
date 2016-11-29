#pragma once
#include "template.h"
#include "color.h"


class Material {
private:
	//Color color;
	 // just for now
public:
	Color color;
	Material(Color color);
	Color getColor() { return color; };
};