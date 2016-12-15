#pragma once
#include <string>
#include "triangle.h"
#include <vector>
class ObjectLoader {
public:
	std::vector<Triangle*> loadObject(const std::string filename);
	ImportObject* loadObjectImportObject(const std::string filename);
};