#pragma once

#include "surface.h"
#include "ray.h"
#include "camera.h"

class Raytracer {
private:
	//Scene scene;
	Camera camera;
	void trace(Ray r);
public:
	Raytracer(Camera camera);
	void traceScreen(Tmpl8::Pixel* screenBuffer, int screenWidth, int screenHeight);
	void tracePixel(Tmpl8::Pixel* pixel, int x, int y);
};