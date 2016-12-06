#include "scene.h"
#include "template.h"


Scene::Scene(Camera* c) :
	camera(c) {

}

Scene::~Scene() {
	for (std::vector< Object* >::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		delete (*it);
	}
	for (std::vector< Light* >::iterator it = lights.begin(); it != lights.end(); ++it)
	{
		delete (*it);
	}
	lights.clear();
}

void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}

std::vector<Object*> Scene::getObjects() {
	return objects;
}

void Scene::addLight(Light* light) {
	lights.push_back(light);
}

std::vector<Light*> Scene::getLights() {
	return lights;
}

void Scene::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material, float* distance) {
	*distance = INFINITE;
	for (int i = 0; i < objects.size(); i++) {
		float tempDistance = INFINITE;
		glm::vec3 result = objects[i]->intersection(r, &tempDistance);
		//std::cout << "x: " << result.x << "y: " << result.y << "z: " << result.z << std::endl;
		if (*distance > tempDistance && tempDistance > 0) {
			*distance = tempDistance;
			*normal = result;
			*material = *objects[i]->getMaterial();
		}
		
		//std::cout << objects[i]->getPosition().x << std::endl;
	}
	if (*distance != INFINITE) {
		*intersection = r.getOrigin() + *distance * r.getDirection();
	}
}

bool Scene::isThereAIntersection(Ray r, float distanceResult){
	float distance = INFINITE;
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->intersection(r, &distance);
		float floatError = 0.01; //otherwise black lines where it shouldnt be
		if (distance <= distanceResult && distance >= 0 + floatError) {
			return false;
		}
	}
	return true;
}