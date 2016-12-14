#pragma once

#include "surface.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "material.h"
#include "color.h"

class Raytracer {
private:
	Scene* scene;
	Camera* camera;
	Color trace(Ray r, int counter);
	void nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance);
	Color directIllumination(glm::vec3 intersection, glm::vec3 normal, float* angle);
	bool canReachLight(glm::vec3 position, glm::vec3 direction, glm::vec3 normal, float distanceResult);
public:
	Raytracer(Scene* scene, Camera* camera);
	void traceScreen(Tmpl8::Pixel* screenBuffer, const int screenWidth, const int screenHeight);
	void tracePixel(Tmpl8::Pixel* pixel, const int x, const int y);
};