#pragma once
#include "camera.h"
#include "object.h"
#include "ray.h"
#include "template.h"
#include <vector>
#include "material.h"

class Scene {
private:
	Camera* camera;
	std::vector<Object*> objects;

public:
	Scene(Camera* c);
	void addObject(Object* obj);
	std::vector<Object*> getObjects();
	void nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material);
};