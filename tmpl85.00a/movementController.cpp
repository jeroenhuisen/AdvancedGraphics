#include "template.h"

#include "movementController.h"

MovementController::MovementController(Camera* camera) :
	camera(camera) { //add movement?

}

void MovementController::update() {
	camera->changePosition(movement);
	camera->changeDirection(direction);
	camera->moveCamera();
	movement = glm::vec3(0, 0, 0);
	direction = glm::vec3(0, 0, 0);
}

// movement distance depends on the time passed making it FPS independent but jumps with this tracer
void MovementController::update(float dt) {
	movement *= dt;
	direction *= dt;
	update();
}

void MovementController::forward() {
	movement += glm::vec3(0, movementSpeed, 0);
}
void MovementController::back() {
	movement += glm::vec3(0, -movementSpeed, 0);
}
void MovementController::left() {
	movement += glm::vec3(-movementSpeed, 0, 0);
}
void MovementController::right() {
	movement += glm::vec3(movementSpeed, 0, 0);
}
void MovementController::up() {
	movement += glm::vec3(0, 0, -movementSpeed);
}
void MovementController::down() {
	movement += glm::vec3(0, 0, movementSpeed);
}

void MovementController::cameraUp() {
	direction += glm::vec3(0, 0, -directionSpeed);
}
void MovementController::cameraDown() {
	direction += glm::vec3(0, 0, directionSpeed);
}
void MovementController::cameraLeft() {
	direction += glm::vec3(-directionSpeed, 0, 0);
}
void MovementController::cameraRight() {
	direction += glm::vec3(directionSpeed, 0, 0);
}



