#include "template.h"

#include "sceneBuilder.h"

void sceneBuilder(Scene* scene) {
	//Material* red = new Material(0xff0000);
	//Sphere* sphere = new Sphere(glm::vec3(10.0f,10.0f,10.0f), 2.0f, red);
	//scene->addObject(sphere);



	Material* mirror = new Material(Color(0xFF, 0xFF, 0xFF), 1);
	Material* red = new Material(Color(0xFF, 0, 0));
	Material* green = new Material(Color(0, 0xFF, 0));
	Material* redish = new Material(Color(0x1F, 0, 0));
	Material* greenish = new Material(Color(0, 0x1f, 0));
	Material* blueish = new Material(Color(0, 0, 0x1F), 0, 1);
	Material* whitish = new Material(Color(0x1f, 0x1f, 0xff), 0.5f);
	Material* pink = new Material(Color(0xFF, 0x00, 0xFF));
	Sphere* sphereR = new Sphere(glm::vec3(300.0f, 1100.0f, 200.0f), 100.0f, red);
	Sphere* sphereG = new Sphere(glm::vec3(0.0f, 1100.0f, 200.0f), 100.0f, green);
	Sphere* sphereB = new Sphere(glm::vec3(-300.0f, 1100.0f, 200.0f), 100.0f, blueish);
/*	Plane* plane = new Plane(glm::vec3(0, 1108, 0), glm::vec3(0, 1, 0), redish);
	Plane* plane1 = new Plane(glm::vec3(500, 1108, 400), glm::vec3(0, 0, -1), red);*/
	Triangle* triangle = new Triangle(glm::vec3(0, 900, 0), glm::vec3(200, 1000, 0), glm::vec3(100, 900, 100), redish);
	PointLight* pointLight = new PointLight(glm::vec3(0, 0, -200), 2000, Color(0xFF, 0xFF, 0xFF), 1.0f, 0.007f, 0.002f);
	PointLight* pointLightSmall = new PointLight(glm::vec3(70, 1000, 0), 1000, Color(0xFF, 0x00, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall1 = new PointLight(glm::vec3(200, 1000, 0), 1000, Color(0xFF, 0x00, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall2 = new PointLight(glm::vec3(-30, 1000, -250), 1000, Color(0x00, 0xFF, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall3 = new PointLight(glm::vec3(-500, 1000, 0), 1000, Color(0x00, 0xFF, 0xFF), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall4 = new PointLight(glm::vec3(-500, 1500, 0), 1000, Color(0x00, 0xFF, 0xFF), 1.0f, 1.0f, 0.05f);
	scene->addLight(pointLight);
	//scene->addLight(pointLightSmall);
	/*scene->addLight(pointLightSmall1);
	scene->addLight(pointLightSmall2);
	scene->addLight(pointLightSmall3);
	scene->addLight(pointLightSmall4);*/
	//scene->addObject(plane);
	//scene->addObject(plane1);
	//scene->addObject(triangle);
//	scene->addObject(sphereR);
	//scene->addObject(sphereG);
//	scene->addObject(sphereB);




	Material* gray = new Material(Color(0xD3, 0xD3, 0xD3));
/*	Plane * boxBottom = new Plane(glm::vec3(0, 1100, 400), glm::vec3(0, 0, -1), gray);
	Plane * boxBack = new Plane(glm::vec3(0, 2000, 0), glm::vec3(0, -1, 0), mirror);
	Plane * boxFront = new Plane(glm::vec3(0, -200, 0), glm::vec3(0, 1, 0), pink);
	Plane * boxLeft = new Plane(glm::vec3(-600, 1100, 0), glm::vec3(1, 0, 0), gray);
	Plane * boxRight = new Plane(glm::vec3(600, 1100, 0), glm::vec3(-1, 0, 0), gray);
	Plane * boxRoof = new Plane(glm::vec3(0, 1100, -400), glm::vec3(0, 0, 1), gray);
	scene->addObject(boxBack);
	scene->addObject(boxLeft);
	scene->addObject(boxRight);
	scene->addObject(boxRoof);
	scene->addObject(boxFront);
	scene->addObject(boxBottom);*/
	//scene->addObject(sphere);

	Sphere* mirrorSphere = new Sphere(glm::vec3(10.0f, 1100.0f, 200.0f), 100.0f, mirror);
	//scene->addObject(mirrorSphere);

	ObjectLoader objectLoader;
	//std::vector<Triangle*> triangles = objectLoader.loadObject("importOBJ/box.obj");

	int objSize = 0;
	ImportObject* obj = objectLoader.loadObjectImportObject("importOBJ/windmill.obj", &objSize);
	ImportObject* a = obj;
	for (int i = 0; i < objSize; i++) {
		a->move(glm::vec3(250, 1000, 0));
		a->material = red;
		scene->addObject(a);
		a++;
	}

	BVH testBVH;
	testBVH.constructBVH(obj->triangles, obj->amount);
	std::cout << "BVH has been build" << std::endl;
	//scene->addObject(obj);

	//ImportObject* test = new ImportObject(glm::vec3(250, 1000, 0), glm::vec3(0, -1, 0), red, obj->triangles, obj->amount);
	/*for (Triangle* t : triangles) {
		t->material = red;
		scene->addObject(t);
	}*/



}