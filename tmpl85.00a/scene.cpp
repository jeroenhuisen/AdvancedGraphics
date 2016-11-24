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

void Scene::nearestIntersection(Ray r, glm::vec3* intersection, glm::vec3* normal, Material* material) {
	for (int i = 0; i < objects.size(); i++) {
		glm::vec3 result = objects[i]->intersection(r);
		//std::cout << "x: " << result.x << "y: " << result.y << "z: " << result.z << std::endl;

		//just assume it is for now
		*intersection = result;
		//*material = objects[i]->getMaterial();
		if (result.x != 0) {
			*material = *objects[i]->getMaterial();
		}
		//std::cout << objects[i]->getPosition().x << std::endl;
	}
}