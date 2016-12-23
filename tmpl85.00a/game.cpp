#include "template.h"

// doing this in the init doesnt work :)
Game::Game() :
	camera(SCRWIDTH, SCRHEIGHT, 60, vec3(0, 100,100), vec3(0, 1.0, 0.0f)), scene(&camera), tracer(&scene, &camera), movementController(&camera), buttonHandler(&movementController), guiBuilder(screen, &camera) {//screen isnt init yet

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
	sceneBuilder(&scene);
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
	buttonHandler.updateKeys();
	//	movementController.update(dt);
	movementController.update();
	tracer.traceScreen(screen->GetBuffer(), SCRWIDTH, SCRHEIGHT);
	guiBuilder.draw();
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

