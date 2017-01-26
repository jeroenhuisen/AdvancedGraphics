#pragma once
#include <string>
#include "Triangle.h"
#include <vector>
#include <iostream>
class ObjectImporter {
public:
	std::vector<Triangle> loadObject(const std::string filename);
	//ImportObject* loadObjectImportObject(const std::string filename, int* objSize);
};