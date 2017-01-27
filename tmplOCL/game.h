#pragma once
#include "Camera.h"
#include "ButtonHandler.h"
#include "MovementController.h"

namespace ocllab {

class Game
{
private:
	timer timer;
	cl_mem writeBuffer;
	cl_float3 pos;
	int* ptr;
	int len;
	Camera* camera = new Camera();
	MovementController* movementController = new MovementController(camera);
	ButtonHandler* buttonHandler = new ButtonHandler(movementController);
public:
	bool Init();
	void Tick();
	void Shutdown();
	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	void MouseMove( int x, int y ) {}
	void MouseClick() {}
};

}

// EOF