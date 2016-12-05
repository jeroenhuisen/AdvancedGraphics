#pragma once

#include "camera.h"

class MovementController {
private:
	Camera* camera;
	glm::vec3 movement;
	float movementSpeed = 100;

public:
	MovementController(Camera * camera);

	void forward();
	void back();
	void left();
	void right();
	void up();
	void down();
	void update();
	
};