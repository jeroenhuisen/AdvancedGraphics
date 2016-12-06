#include "template.h"

// doing this in the init doesnt work :)
Game::Game() :
	camera(SCRWIDTH, SCRHEIGHT, 60, vec3(0,100,200), vec3(0, 1.0, 0.0f)), scene(&camera), tracer(&scene, &camera), movementController(&camera), buttonHandler(&movementController), guiBuilder(screen, &camera) {//screen isnt init yet

}

// -----------------------------------------------------------
// Initialize the game
// -----------------------------------------------------------
void Game::Init()
{	
	guiBuilder= GUIBuilder(screen, &camera);//screen isnt init yet
	//Camera camera(SCRWIDTH, SCRHEIGHT, 60);
	//Scene scene(&camera);
	//tracer = Raytracer(&scene, &camera);
	Material* mirror = new Material(Color(0xFF, 0xFF, 0xFF), 1);

	Material* red = new Material(Color(0xFF,0,0));
	Material* green = new Material(Color(0,0xFF,0));
	Material* redish = new Material(Color(0x1F, 0, 0));
	Material* greenish = new Material(Color(0, 0x1f, 0));
	Material* blueish = new Material(Color(0, 0, 0x1F), 0, 1);
	Material* pink = new Material(Color(0xFF, 0x00, 0xFF));
	Sphere* sphereR = new Sphere(glm::vec3(300.0f, 1100.0f, 200.0f), 100.0f, mirror);
	Sphere* sphereG = new Sphere(glm::vec3(0.0f, 1100.0f, 200.0f), 100.0f, greenish);
	Sphere* sphereB = new Sphere(glm::vec3(-300.0f, 1100.0f, 200.0f), 100.0f, blueish);
	Plane* plane = new Plane(glm::vec3(0, 1108, 0), glm::vec3(0, 1, 0), 100, 100, redish);
	Plane* plane1 = new Plane(glm::vec3(500, 1108, 400),  glm::vec3(0, 0, -1), 100, 100, red);
	Triangle* triangle = new Triangle(glm::vec3(0, 900, 0), glm::vec3(200, 1000, 0), glm::vec3(100, 900, 100), redish);
	PointLight* pointLight = new PointLight(glm::vec3(0, 0, -200), 2000, Color(0xFF,0xFF,0xFF), 1.0f, 0.007f, 0.002f);
	PointLight* pointLightSmall = new PointLight(glm::vec3(70, 1000, 0), 1000, Color(0x00,0x00,0x00), 1.0f, 0.2f, 0.05f); 
	PointLight* pointLightSmall1 = new PointLight(glm::vec3(200, 1000, 0), 1000, Color(0xFF, 0x00, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall2 = new PointLight(glm::vec3(-30, 1000, -250), 1000, Color(0x00, 0xFF, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall3 = new PointLight(glm::vec3(-265, 1000, 0), 1000, Color(0x00, 0xFF, 0xFF), 1.0f, 0.2f, 0.05f);
	scene.addLight(pointLight);
	//scene.addLight(pointLightSmall);
	//scene.addLight(pointLightSmall1);
	//scene.addLight(pointLightSmall2);
	//scene.addLight(pointLightSmall3);
								//scene.addObject(plane);
	//scene.addObject(plane1);
	//scene.addObject(triangle);
	scene.addObject(sphereR);
	//scene.addObject(sphereG);
	scene.addObject(sphereB);




	Material* gray = new Material(Color(0xD3, 0xD3, 0xD3));
	Plane * boxBottom = new Plane(glm::vec3(0, 1100, 400), glm::vec3(0, 0, -1), 1000, 1000, red);
	Plane * boxBack = new Plane(glm::vec3(0, 2000, 0), glm::vec3(0, -1, 0), 500, 500, mirror);
	Plane * boxFront = new Plane(glm::vec3(0, -200, 0), glm::vec3(0, 1, 0), 500, 500, pink);
	Plane * boxLeft = new Plane(glm::vec3(-600, 1100, 0), glm::vec3(1, 0, 0), 1000, 1000, gray);
	Plane * boxRight = new Plane(glm::vec3(600, 1100, 0), glm::vec3(-1, 0, 0), 1000, 1000, gray);
	Plane * boxRoof = new Plane(glm::vec3(0, 1100, -400), glm::vec3(0, 0, 1), 1000, 1000, green);
	scene.addObject(boxBack);
	scene.addObject(boxLeft);
	scene.addObject(boxRight);
	scene.addObject(boxRoof);
	scene.addObject(boxFront);
	scene.addObject(boxBottom);
	//scene.addObject(sphere);
	//sceneBuilder(&scene);

	Sphere* mirrorSphere = new Sphere(glm::vec3(10.0f, 1100.0f, 200.0f), 100.0f, mirror);
	scene.addObject(mirrorSphere);
}

// -----------------------------------------------------------
// Input handling
// -----------------------------------------------------------
void Game::HandleInput( float dt )
{
}

// -----------------------------------------------------------
// Main game tick function
// -----------------------------------------------------------
void Game::Tick( float dt )
{
	screen->Clear( 0 );
	tracer.traceScreen(screen->GetBuffer(), SCRWIDTH, SCRHEIGHT);
	guiBuilder.draw();
	buttonHandler.updateKeys();
	movementController.update(dt);
	//screen->Line( 2, 10, 50, 10, 0xff0000 );
	std::cout << dt << std::endl;
}


void Game::KeyDown(int a_Key) {
	buttonHandler.addButton(a_Key);
	//std::cout << a_Key << std::endl;
}

void Game::KeyUp(int a_Key) {
	buttonHandler.removeButton(a_Key);
	//std::cout << "up: " << a_Key << std::endl;
}

