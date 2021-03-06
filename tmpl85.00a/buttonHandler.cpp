#include "template.h"

#include "buttonHandler.h"

ButtonHandler::ButtonHandler(MovementController* movement):
movement(movement){

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
			case SDL_SCANCODE_W:  // w forward
				movement->forward();
				break;
			case SDL_SCANCODE_S: // s backwards
				movement->back();
				break;
			case SDL_SCANCODE_A:  //a
				movement->left();
				break;
			case SDL_SCANCODE_D: //d
				movement->right();
				break;
			case SDL_SCANCODE_Q: //q
				movement->up();
				break;
			case SDL_SCANCODE_E: //e
				movement->down();
				break;		
			case SDL_SCANCODE_UP: //arrow up
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
				break;
		}
	}
	//movement->update(); //use update so only camera movement only gets calculated once instead of multiple times small optimisation

}