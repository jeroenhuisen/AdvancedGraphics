#include "template.h"

#include "material.h"

Material::Material(Color color, float reflectioness) : 
	color(color), reflectioness(reflectioness) {
	//->reflectioness = reflectioness;
	if (this->reflectioness > 1) {
		this->reflectioness = 1;
	}
}

//Values between 0 and 1
float Material::getReflectioness() {
	return reflectioness;
}