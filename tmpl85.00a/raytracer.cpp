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
	glm::vec3 intersection;
	glm::vec3 normal;
	Material material(0x000000);
	nearestIntersection(r, &intersection, &normal, &material);
	//

	return material.getColor() * directIllumination(intersection, normal);
}

void Raytracer::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material) {
	// going for the slowest approach
	scene->nearestIntersection(r, intersection, normal, material);
}

Tmpl8::Pixel Raytracer::directIllumination(glm::vec3 intersection, glm::vec3 normal) {
	Ray r = Ray(intersection, normal);
	std::vector<Light*> lights = scene->getLights();
	for (int i = 0; i < lights.size(); i++) {
//		lights[i].
	}
	return 0xFFFFFF;
}

