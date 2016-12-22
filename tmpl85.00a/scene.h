#pragma once
#include "camera.h"
#include "object.h"
#include "ray.h"
#include "template.h"
#include <vector>
#include "material.h"
#include "BVH.h"

#include "light.h"
//note lights cant be seen directly :( like the sun so fuck :(

class Scene {
private:
	Camera* camera;
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	BVH* bvh;

public:
	Scene(Camera* c);
	~Scene();
	void addObject(Object* obj);
	void addLight( Light* light);
	void addBVH(BVH* bvh);
	std::vector<Object*> getObjects();
	std::vector<Light*> getLights();
	void nearestIntersection(const Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance);
	bool isThereAIntersection(const Ray r, const float distanceResult);
};