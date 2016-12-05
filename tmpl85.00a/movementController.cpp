#include "template.h"

#include "movementController.h"

MovementController::MovementController(Camera* camera) :
	camera(camera) { //add movement?

}

void MovementController::update() {
	camera->changePosition(movement);
	camera->moveCamera();
	movement = glm::vec3(0, 0, 0);
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

