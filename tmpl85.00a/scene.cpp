#include "scene.h"
#include "template.h"


Scene::Scene(Camera* c) :
	camera(c) {

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

void Scene::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material) {
	float distance = INFINITE;
	for (int i = 0; i < objects.size(); i++) {
		float tempDistance = INFINITE;
		glm::vec3 result = objects[i]->intersection(r, &tempDistance);
		//std::cout << "x: " << result.x << "y: " << result.y << "z: " << result.z << std::endl;
		if (distance > tempDistance) {
			distance = tempDistance;
			*intersection = result;
			*material = *objects[i]->getMaterial();
		}
		
		//std::cout << objects[i]->getPosition().x << std::endl;
	}
}