#pragma once
#include "camera.h"
#include "object.h"
#include "ray.h"
#include "template.h"
#include <vector>
#include "material.h"

#include "light.h"
//note lights cant be seen directly :( like the sun so fuck :(

class Scene {
private:
	Camera* camera;
	std::vector<Object*> objects;
	std::vector<Light*> lights;

public:
	Scene(Camera* c);
	void addObject(Object* obj);
	void addLight(Light* light);
	std::vector<Object*> getObjects();
	std::vector<Light*> getLights();
	void nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance);
	bool isThereAIntersection(Ray r, float distanceResult);
};