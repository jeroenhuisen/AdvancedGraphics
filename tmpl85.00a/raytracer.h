#pragma once

#include "surface.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"
#include "material.h"

class Raytracer {
private:
	Scene* scene;
	Camera* camera;
	Tmpl8::Pixel trace(Ray r);
	void nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material);
	Tmpl8::Pixel directIllumination(glm::vec3 intersection, glm::vec3 normal);
public:
	Raytracer(Scene* scene, Camera* camera);
	void traceScreen(Tmpl8::Pixel* screenBuffer, int screenWidth, int screenHeight);
	void tracePixel(Tmpl8::Pixel* pixel, int x, int y);
};