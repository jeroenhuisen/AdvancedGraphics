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
	*pixel = trace(r,0);
}

Tmpl8::Pixel Raytracer::trace(Ray r, int counter) {
	if (counter >= 10) {
		return 0x000000;
	}
	//I, N, mat = nearestIntersection(scene, r);
	glm::vec3 intersection;
	glm::vec3 normal;
	Material material(0x000000);
	float distance = INFINITE;
	nearestIntersection(r, &intersection, &normal, &material, &distance);
	
	if (material.getColor() != 0) {
		float mul = directIllumination(intersection, normal, distance);
		//if (mat == MIRROR)
		//return material.getColor() * trace(Ray(intersection, reflect(r.getDirection(), normal)), ++counter);
		
		//Tmpl8::Pixel test = Tmpl8::Pixel((material.getColor() & 0xFF0000) * mul + (material.getColor()&0x00FF00) * mul + (material.getColor()&0x0000FF) * mul);
		//Tmpl8::Pixel test2 = material.getColor();// *mul;
		unsigned long r = (material.getColor() & 0xFF0000) * mul;
		unsigned long ra = r & 0xFF0000; //maybe round?
		unsigned long g = (material.getColor() & 0x00FF00) * mul;
		unsigned long ga = g & 0x00FF00;
		unsigned long b = (material.getColor() & 0x0000FF)* mul;
		unsigned long ba = b & 0x0000FF;
		unsigned long rgb = ra + ga + ba;
		return rgb;
	}
	
		
	return 0x000000;
	//return material.getColor() * directIllumination(intersection, normal, distance);

}

void Raytracer::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance) {
	// going for the slowest approach
	scene->nearestIntersection(r, intersection, normal, material, distance);
}

float Raytracer::directIllumination(glm::vec3 intersection, glm::vec3 normal, float distance) {
	// Color of the lights are fully ignored at the moment...
	Ray r = Ray(intersection, normal);
	std::vector<Light*> lights = scene->getLights();
	for (int i = 0; i < lights.size(); i++) {
		// wrong implementation
		return lights[i]->calculateStrength(distance);
	}
	//return 0xFFFFFF;
}

