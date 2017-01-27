#include "system.h"
#include <OpenGL\glm\mat4x4.hpp>

#include "movementController.h"

MovementController::MovementController(Camera* camera): camera(camera), movement({0.0f, 0.0f, 0.0f}), direction({ 0.0f, 0.0f, 0.0f })
{ //add movement?

}

void MovementController::update() {
	camera->changePosition(movement);
	camera->changeDirection(direction);
	movement = vec3(0, 0, 0);
	direction = vec3(0, 0, 0);
}

// movement distance depends on the time passed making it FPS independent but jumps with this tracer
void MovementController::update(const float dt) {
	movement *= dt*0.001; // divide by 1000 since dt is in millisec (otherwise the movementspeed should be really small)
	direction *= dt*0.001;
	update();
}

void MovementController::forward() {
	movement += vec3(0, 0, movementSpeed);
}
void MovementController::back() {
	movement += vec3(0, 0, -movementSpeed);
}
void MovementController::left() {
	movement += vec3(-movementSpeed, 0, 0);
}
void MovementController::right() {
	movement += vec3(movementSpeed, 0, 0);
}
void MovementController::up() {
	movement += vec3(0, movementSpeed, 0);
}
void MovementController::down() {
	movement += vec3(0, -movementSpeed, 0);
}

/*void MovementController::cameraUp() {
	direction += vec3(0, 0, -directionSpeed);
}
void MovementController::cameraDown() {
	direction += vec3(0, 0, directionSpeed);
}
void MovementController::cameraLeft() {
	direction += vec3(-directionSpeed, 0, 0);
}
void MovementController::cameraRight() {
	direction += vec3(directionSpeed, 0, 0);
}*/
