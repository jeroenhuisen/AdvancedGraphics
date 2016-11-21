#include "raytracer.h"
#include "template.h"

Raytracer::Raytracer(Scene* scene, Camera* camera): 
	scene(scene), camera(camera) {

}

void Raytracer::traceScreen(Tmpl8::Pixel* screenBuffer, int screenWidth, int screenHeight) {
	for (int y = 0; y < screenHeight; y++){
		for (int x = 0; x < screenWidth; x++) {
			screenBuffer++; //hoping that this is how the buffer is alligned
			tracePixel(screenBuffer, x, y);
		}
	}
}

void Raytracer::tracePixel(Tmpl8::Pixel* pixel, int x, int y) {
	// do stuff
	Ray r = Ray(camera->getPosition(), camera->getPixelDirection(x, y));
	*pixel = trace(r);
}

Tmpl8::Pixel Raytracer::trace(Ray r) {
	//I, N, mat = nearestIntersection(scene, r);
	// Red test
	return Tmpl8::Pixel(0xff0000);
}