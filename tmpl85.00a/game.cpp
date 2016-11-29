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


	Material* red = new Material(Color(0xFF,0,0));
	Material* green = new Material(Color(0,0xFF,0));
	Material* redish = new Material(Color(0x1F, 0, 0));
	Sphere* sphere = new Sphere(glm::vec3(10.0f, 10.0f, 10.0f), 2.0f, red);
	Plane* plane = new Plane(glm::vec3(0, 1108, 0), glm::vec3(0, 1, 0), 100, 100, redish);
	Plane* plane1 = new Plane(glm::vec3(500, 1108, 300),  glm::vec3(0.1, 0.4, 0.5), 100, 100, red);
	PointLight* pointLight = new PointLight(glm::vec3(0, 0, 0), 10000, Color(0xFF,0xFF,0xFF), 1.0f, 0.007f, 0.002f);
	PointLight* pointLightSmall = new PointLight(glm::vec3(0, 1100, 0), 1000, Color(0xFF,0xFF,0xFF), 1.0f, 0.7f, 0.5f); //distance is 8 on closes point I/(1.0+0.7*8+0.5*8^2)
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