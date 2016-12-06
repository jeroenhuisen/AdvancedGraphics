#pragma once

#include "camera.h"

class MovementController {
private:
	Camera* camera;
	glm::vec3 movement, direction;
	float movementSpeed = 100;
	float directionSpeed = 0.1;

public:
	MovementController(Camera * camera);

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
	void update(float dt);
};