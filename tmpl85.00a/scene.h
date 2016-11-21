#pragma once
#include "camera.h"
#include "object.h"
#include "template.h"
#include <vector>

class Scene {
private:
	Camera* camera;
	std::vector<Object*> objects;

public:
	Scene(Camera* c);
	void addObject(Object* obj);
};