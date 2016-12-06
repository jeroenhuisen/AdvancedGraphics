#pragma once
#include <string>
#include "triangle.h"
#include <vector>
class ObjectLoader {
public:
	std::vector<Triangle*> loadObject(std::string filename);
};