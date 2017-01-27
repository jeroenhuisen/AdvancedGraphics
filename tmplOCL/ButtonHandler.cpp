#include "system.h"

#include "buttonHandler.h"

ButtonHandler::ButtonHandler(MovementController* movement) :
	movement(movement) {

}

void ButtonHandler::addButton(const int button) {
	buttons.insert(button);
}

void ButtonHandler::removeButton(const int button) {
	buttons.erase(button);
}

void ButtonHandler::updateKeys() {
	for (int button : buttons) {
		switch (button) {
		case int('W'):  // w forward
			movement->forward();
			break;
		case int('S'): // s backwards
			movement->back();
			break;
		case int('A'):  //a
			movement->left();
			break;
		case int('D'): //d
			movement->right();
			break;
		case int('Q'): //q
			movement->up();
			break;
		case int('E'): //e
			movement->down();
			break;
		/*case SDL_SCANCODE_UP: //arrow up
			movement->cameraUp();
			break;
		case SDL_SCANCODE_DOWN:
			movement->cameraDown();
			break;
		case SDL_SCANCODE_LEFT:
			movement->cameraLeft();
			break;
		case SDL_SCANCODE_RIGHT:
			movement->cameraRight();
			break;*/
		}
	}
	//movement->update(); //use update so only camera movement only gets calculated once instead of multiple times small optimisation

}