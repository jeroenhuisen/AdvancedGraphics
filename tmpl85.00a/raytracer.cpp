#include "raytracer.h"
#include "template.h"

Raytracer::Raytracer(Scene* scene, Camera* camera): 
	scene(scene), camera(camera) {

}

void Raytracer::traceScreen(Tmpl8::Pixel* screenBuffer, int screenWidth, int screenHeight) {
	//Tmpl8::Pixel color = 0x000000;
	//boolean test = true;
	//int testCounter = 0;
	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			screenBuffer++; //hoping that this is how the buffer is alligned
			tracePixel(screenBuffer, x, y);
			if (x == screenWidth/2 && y == screenHeight/2){
				*screenBuffer = 0x00FF00;
			}
			if (x == screenWidth / 2  && y == screenHeight/2 + 100) {
				*screenBuffer = 0x00FF00;
			}
			if (x == screenWidth / 2  + 100 && y == screenHeight/2) {
				*screenBuffer = 0x00FF00;
			}
			if (x == screenWidth / 2  + 100 && y == screenHeight / 2 + 100) {
				*screenBuffer = 0x00FF00;
			}
			//*screenBuffer = color;
			/*if (testCounter >= 10) {
				if (test) {
					color = 0x770000;

					test = false;
				}
				else {
					color = 0x000077;
					test = true;
				}
				testCounter = 0;
			
			}
			testCounter++;*/
		}
		/*if (testCounter >= 10) { 
			if (test) {
				color = 0x770000;

				test = false;
			}
			else {

				color = 0x000077;
				test = true;
			}
			testCounter = 0;
		}
		testCounter++;*/
	}
}

void Raytracer::tracePixel(Tmpl8::Pixel* pixel, int x, int y) {
	// do stuff
	Ray r = Ray(camera->getPosition(), camera->getPixelDirection(x, y));
	*pixel = trace(r);
}

Tmpl8::Pixel Raytracer::trace(Ray r) {
	//I, N, mat = nearestIntersection(scene, r);
	// Black test
	glm::vec3 intersection;
	glm::vec3 normal;
	Material material(0x000000);
	nearestIntersection(r, &intersection, &normal, &material);
	return material.getColor();
}

void Raytracer::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material) {
	// going for the slowest approach
	scene->nearestIntersection(r, intersection, normal, material);
}

