#include "template.h"

// doing this in the init doesnt work :)
Game::Game() :
	camera(SCRWIDTH, SCRHEIGHT, 60, vec3(1,0,0), vec3(0, 1.0, 0.0f)), scene(&camera), tracer(&scene, &camera) {

}

// -----------------------------------------------------------
// Initialize the game
// -----------------------------------------------------------
void Game::Init()
{	
	//Camera camera(SCRWIDTH, SCRHEIGHT, 60);
	//Scene scene(&camera);
	//tracer = Raytracer(&scene, &camera);


	Material* red = new Material(Color(0xFF,0,0));
	Material* green = new Material(Color(0,0xFF,0));
	Material* redish = new Material(Color(0x1F, 0, 0));
	Sphere* sphere = new Sphere(glm::vec3(10.0f, 1100.0f, 10.0f), 100.0f, red);
	Plane* plane = new Plane(glm::vec3(0, 1108, 0), glm::vec3(0, 1, 0), 100, 100, redish);
	Plane* plane1 = new Plane(glm::vec3(500, 1108, 400),  glm::vec3(0, 0, 1), 100, 100, red);
	PointLight* pointLight = new PointLight(glm::vec3(0, 0, 0), 5000, Color(0xFF,0xFF,0xFF), 1.0f, 0.007f, 0.002f);
	PointLight* pointLightSmall = new PointLight(glm::vec3(70, 1100, 0), 1000, Color(0x00,0x00,0x00), 1.0f, 0.2f, 0.05f); 
	PointLight* pointLightSmall1 = new PointLight(glm::vec3(200, 1100, 0), 1000, Color(0xFF, 0x00, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall2 = new PointLight(glm::vec3(-30, 1100, -250), 1000, Color(0x00, 0xFF, 0x00), 1.0f, 0.2f, 0.05f);
	PointLight* pointLightSmall3 = new PointLight(glm::vec3(-265, 1100, 0), 1000, Color(0x00, 0xFF, 0xFF), 1.0f, 0.2f, 0.05f);
	//scene.addLight(pointLight);
	scene.addLight(pointLightSmall);
	scene.addLight(pointLightSmall1);
	scene.addLight(pointLightSmall2);
	scene.addLight(pointLightSmall3);
								//scene.addObject(plane);
	scene.addObject(plane1);
	scene.addObject(sphere);

	Material* gray = new Material(Color(0xD3, 0xD3, 0xD3));
	Plane * boxBottom = new Plane(glm::vec3(0, 1100, 400), glm::vec3(0, 0, 1), 1000, 1000, gray);
	Plane * boxBack = new Plane(glm::vec3(0, 2000, 0), glm::vec3(0, 1, 0), 500, 500, green);
	Plane * boxLeft = new Plane(glm::vec3(600, 1100, 0), glm::vec3(1, 0, 0), 1000, 1000, gray);
	Plane * boxRight = new Plane(glm::vec3(-600, 1100, 0), glm::vec3(1, 0, 0), 1000, 1000, gray);
	scene.addObject(boxBack);
	scene.addObject(boxLeft);
	scene.addObject(boxRight);
	//scene.addObject(boxBottom);
	//scene.addObject(sphere);
	//sceneBuilder(&scene);


	Material* mirror = new Material(Color(0xFF, 0xFF, 0xFF), 1);
	Sphere* mirrorSphere = new Sphere(glm::vec3(10.0f, 1500.0f, 10.0f), 1000.0f, mirror);
	//scene.addObject(mirrorSphere);
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
	screen->Print( "hello world", 2, 2, 0xffffff );
	//screen->Line( 2, 10, 50, 10, 0xff0000 );
	std::cout << dt << std::endl;
}