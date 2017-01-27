#pragma once

#include "system.h"
#include "Camera.h"

class MovementController {
private:
	vec3 movement, direction;
	float movementSpeed = 1;
	float directionSpeed = 0.1f;
	Camera* camera;

public:
	MovementController(Camera* camera);

	void forward();
	void back();
	void left();
	void right();
	void up();
	void down();

	void cameraUp();
	void cameraDown();
	void cameraLeft();
	void cameraRight();


	void update();
	void update(const float dt);
};
