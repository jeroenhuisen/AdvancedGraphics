#include "template.h"

#include "raytracer.h"

Raytracer::Raytracer(Scene* scene, Camera* camera): 
	scene(scene), camera(camera) {
	/*jm = JobManager::GetJobManager();
	t1 = new TestJob(this);
	t2 = new TestJob(this);
	t3 = new TestJob(this);
	t4 = new TestJob(this);
	jm->AddJob2(t1);
	jm->AddJob2(t2);
	jm->AddJob2(t3);
	jm->AddJob2(t4);*/
}

void Raytracer::traceScreen(Tmpl8::Pixel* screenBuffer, const int screenWidth, const int screenHeight) {
	//Tmpl8::Pixel color = 0x000000;
	//boolean test = true;
	//int testCounter = 0;
	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			screenBuffer++; //hoping that this is how the buffer is alligned
			tracePixel(screenBuffer, x, y);
			//tracePixel(screenBuffer, x, y);
		}
	}
}

void Raytracer::tracePixel(Tmpl8::Pixel* pixel, const int x, const int y) {
	// do stuff
	Ray r = Ray(camera->position, camera->getPixelDirection(x, y));
	*pixel = trace(r,0).getRGB();
}

Color Raytracer::trace(Ray r, int counter) {
	if (counter >= 10) {
		return Color(0,0,0);
	}
	//I, N, mat = nearestIntersection(scene, r);
	glm::vec3 intersection;
	glm::vec3 normal;
	Material material(Color(0,0,0));
	float distance = INFINITE;
	nearestIntersection(r, &intersection, &normal, &material, &distance);
	
	if (material.getColor().r != 0 || material.getColor().g != 0 || material.getColor().b != 0) {
		float angle = 0;
		if (material.getReflectioness() == 1) {
			//glm::vec3 reflect = r.getDirection() - 2.0f * glm::dot(r.getDirection(), normal) * normal;
			Color reflection = trace(Ray(intersection + 0.1f * glm::reflect(r.direction, normal), glm::reflect(r.direction, normal)), ++counter);
			//Color reflection = trace(Ray(intersection, reflect), ++counter);
			//reflection.to1();
			Color test = material.getColor();
			test.to1();
			Color rgb = test * reflection;
			return rgb;
			//return reflection;
		}
		else if (material.getReflectioness() > 0) {
			Color reflection = trace(Ray(intersection + 0.1f * glm::reflect(r.direction, normal), glm::reflect(r.direction, normal)), ++counter);
			Color diffuse = directIllumination(intersection, normal, &angle);
			reflection.to1();
			Color numbers = (diffuse * (1 - material.getReflectioness()) + reflection * material.getReflectioness());
			return material.getColor() * (diffuse * (1 - material.getReflectioness()) + reflection * material.getReflectioness());
			//exit( NOT_IMPLEMENTED_YET);

		}
		else {
			Color mul = directIllumination(intersection, normal, &angle);	
			//unsigned long rgb = material.getColor().getRGB();
			//Color spec(255 * material.getGlossiness() * pow(angle,8), 255 * material.getGlossiness() * pow(angle, 8), 255 * material.getGlossiness() * pow(angle, 8));
			return material.getColor() * mul;
		}
	}
	
		
	return Color(0,0,0);
	//return material.getColor() * directIllumination(intersection, normal, distance);

}

void Raytracer::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance) {
	// going for the slowest approach
	scene->nearestIntersection(r, intersection, normal, material, distance);
}

Color Raytracer::directIllumination(glm::vec3 intersection, glm::vec3 normal, float* angle) {
	//normal is used to determine which light is more important?

	// Color of the lights are fully ignored at the moment...
	Color c(0, 0, 0);
	//Ray r = Ray(intersection, normal);
	std::vector<Light*> lights = scene->getLights();
	for (int i = 0; i < lights.size(); i++) {
		// wrong implementation
		glm::vec3 direction = lights[i]->position - intersection;
		float distance = glm::length(direction);
		direction = glm::normalize(direction);
		if (canReachLight(intersection, direction, normal, distance)) {
			Color light = lights[i]->getColor();
			light.to1();
			*angle = glm::max(0.0f, glm::dot(normal, direction));
			c += light * lights[i]->calculateStrength(distance) * *angle ;
			//
		}
	}
	return c;
	//return 0xFFFFFF;
}

bool Raytracer::canReachLight(const vec3 origin, const vec3 direction, const vec3 doeEensNormaal, const float distanceResult) {

	Ray r(origin + doeEensNormaal * 0.1f, direction);
	//vector<Object *> objects = scene->getObjects();
	return scene->isThereAIntersection(r,distanceResult);
	
}

/*void Raytracer::calculateGlossiness(Color* c, float glossiness, glm::vec3 normal, Ray r) {
	//angle between normal and the ray deterimines the glossiness / white color (well color of the light
	float angle = glm::length(r.getDirection() - normal);//lower than 1 (most of the time), since it is normilazed 
	*c*= angle*glossiness;
}*/