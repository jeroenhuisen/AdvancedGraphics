#include "template.h"

#include "raytracer.h"

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
	Material material(Color(0,0,0));
	float distance = INFINITE;
	nearestIntersection(r, &intersection, &normal, &material, &distance);
	
	if (material.getColor().r != 0 || material.getColor().g != 0 || material.getColor().b != 0) {
		if (material.getReflectioness() > 0) {
			exit( NOT_IMPLEMENTED_YET);
		}
		else if (material.getReflectioness() == 1) {
			exit(NOT_IMPLEMENTED_YET);
			//return material.getColor() * material.getReflectioness() * trace(Ray(intersection, reflect(r.getDirection(), normal)), ++counter);
		}
		else {
			Color mul = directIllumination(intersection, normal);	
			material.color.r *= mul.r;
			material.color.g *= mul.g;
			material.color.b *= mul.b;
			unsigned long rgb = material.getColor().getRGB();
			return rgb;
		}
		//if (mat == MIRROR)
		//return material.getColor() * trace(Ray(intersection, reflect(r.getDirection(), normal)), ++counter);
		
		//Tmpl8::Pixel test = Tmpl8::Pixel((material.getColor() & 0xFF0000) * mul + (material.getColor()&0x00FF00) * mul + (material.getColor()&0x0000FF) * mul);
		//Tmpl8::Pixel test2 = material.getColor();// *mul;
		/*unsigned long r = (material.getColor() & 0xFF0000) * mul;
		unsigned long ra = r & 0xFF0000; //maybe round? wait if bigger than it will be black and not locked :( so time to fix that
		unsigned long g = (material.getColor() & 0x00FF00) * mul;
		unsigned long ga = g & 0x00FF00;
		unsigned long b = (material.getColor() & 0x0000FF)* mul;
		unsigned long ba = b & 0x0000FF;
		unsigned long rgb = ra + ga + ba;
		return rgb;*/
		//material.getColor().r *= mul;
		//material.getColor().g *= mul;
		//material.getColor().b *= mul;
	}
	
		
	return 0x000000;
	//return material.getColor() * directIllumination(intersection, normal, distance);

}

void Raytracer::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance) {
	// going for the slowest approach
	scene->nearestIntersection(r, intersection, normal, material, distance);
}

Color Raytracer::directIllumination(glm::vec3 intersection, glm::vec3 normal) {
	//normal is used to determine which light is more important?

	// Color of the lights are fully ignored at the moment...
	Color c(0, 0, 0);
	//Ray r = Ray(intersection, normal);
	std::vector<Light*> lights = scene->getLights();
	for (int i = 0; i < lights.size(); i++) {
		// wrong implementation
		glm::vec3 direction = lights[i]->getPosition() - intersection;//maybe normalize it.
		float distance = glm::length(direction);
		direction = glm::normalize(direction);
		if (canReachLight(intersection, direction, distance)) {
			Color light = lights[i]->getColor();
			light.to1();
			c +=  light * lights[i]->calculateStrength(distance);
		}
	}
	return c;
	//return 0xFFFFFF;
}

bool Raytracer::canReachLight(vec3 origin, vec3 direction, float distanceResult) {
	float distance = INFINITE;
	Ray r(origin, direction);
	vector<Object *> objects = scene->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->intersection(r, &distance);
		float floatError = 0.01; //otherwise black lines where it shouldnt be
		if (distance <= distanceResult && distance >= 0 + floatError) {
			return false;
		}
	}
	return true;
}