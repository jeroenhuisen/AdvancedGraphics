#include "scene.h"
#include "template.h"


Scene::Scene(Camera* c) :
	camera(c) {

}

void Scene::addObject(Object* obj) {
	objects.push_back(obj);
}