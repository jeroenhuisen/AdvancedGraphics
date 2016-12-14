#include "template.h"

#include "material.h"

Material::Material(const Color color, const float reflectioness, const float glossiness) : 
	color(color), reflectioness(reflectioness), glossiness(glossiness) {
	//->reflectioness = reflectioness;
	if (this->reflectioness > 1) {
		this->reflectioness = 1;
	}
	else if (this->reflectioness < 0){
		this->reflectioness = 0;
	}

	if (this->glossiness > 1) {
		this->glossiness = 1;
	}
	else if (this->glossiness < 0) {
		this->glossiness = 0;
	}
}

//Values between 0 and 1
float Material::getReflectioness() {
	return reflectioness;
}

float Material::getGlossiness() {
	return glossiness;
}