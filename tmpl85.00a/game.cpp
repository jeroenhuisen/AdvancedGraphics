#include "template.h"

// doing this in the init doesnt work :)
Game::Game() :
	camera(SCRWIDTH, SCRHEIGHT, 60), scene(&camera), tracer(&scene, &camera) {

}

// -----------------------------------------------------------
// Initialize the game
// -----------------------------------------------------------
void Game::Init()
{	
	//Camera camera(SCRWIDTH, SCRHEIGHT, 60);
	//Scene scene(&camera);
	//tracer = Raytracer(&scene, &camera);


	Material* red = new Material(0xff0000);
	Sphere* sphere = new Sphere(glm::vec3(10.0f, 10.0f, 10.0f), 2.0f, red);
	Plane* plane = new Plane(glm::vec3(5, 5, 5), glm::vec3(0, 0.5, 0.5), 10, 100);
	scene.addObject(plane);
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
}