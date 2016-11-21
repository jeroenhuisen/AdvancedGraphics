#pragma once

#include "surface.h"
#include "ray.h"
#include "camera.h"
#include "scene.h"

class Raytracer {
private:
	Scene* scene;
	Camera* camera;
	Tmpl8::Pixel trace(Ray r);
public:
	Raytracer(Scene* scene, Camera* camera);
	void traceScreen(Tmpl8::Pixel* screenBuffer, int screenWidth, int screenHeight);
	void tracePixel(Tmpl8::Pixel* pixel, int x, int y);
};