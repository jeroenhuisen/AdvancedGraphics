#include "template.h"

// doing this in the init doesnt work :)
Game::Game() :
	camera(SCRWIDTH, SCRHEIGHT, 60, vec3(0,0,0), vec3(0, 1.0, 0.0f)), scene(&camera), tracer(&scene, &camera) {

}

// -----------------------------------------------------------
// Initialize the game
// -----------------------------------------------------------
void Game::Init()
{	
	//Camera camera(SCRWIDTH, SCRHEIGHT, 60);
	//Scene scene(&camera);
	//tracer = Raytracer(&scene, &camera);


	Material* red = new Material(0xFF0000);
	Material* green = new Material(0x00FF00);
	Material* redish = new Material(0x1F0000);
	Sphere* sphere = new Sphere(glm::vec3(10.0f, 10.0f, 10.0f), 2.0f, red);
	Plane* plane = new Plane(glm::vec3(0, 1108, 0), glm::vec3(0, 1, 0), 100, 100, redish);
	Plane* plane1 = new Plane(glm::vec3(500, 1108, 300), glm::vec3(0, 0.5, 0.5), 100, 100, red);
	//PointLight* pointLight = new PointLight(glm::vec3(0, 0, 0), 1, 0xFFFFFF, 1.0f, 0.007f, 0.002f);
	PointLight* pointLightSmall = new PointLight(glm::vec3(0, 1000, 0), 1, 0xFFFFFF, 1.0f, 0.07f, 0.02f);
	scene.addLight(pointLightSmall);
	scene.addObject(plane);
	scene.addObject(plane1);
	//scene.addObject(sphere);
	//sceneBuilder(&scene);
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