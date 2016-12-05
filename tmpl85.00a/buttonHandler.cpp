#include "template.h"

#include "buttonHandler.h"

ButtonHandler::ButtonHandler(MovementController* movement):
movement(movement){

}

void ButtonHandler::addButton(int button) {
	buttons.insert(button);
}

void ButtonHandler::removeButton(int button) {
	buttons.erase(button);
}

void ButtonHandler::updateKeys() {
	for (int button : buttons) {
		switch (button) {
			case 26:  // w forward
				movement->forward();
				break;

			case 27: // s backwards
				movement->back();
				break;
			case 23:  //a
				movement->left();
				break;
			case 24: //d
				movement->right();
				break;
			case 6565: //q
				movement->up();
				break;
			case 54: //e
				movement->down();
				break;		
		}
	}
	movement->update(); //use update so only camera movement only gets calculated once instead of multiple times small optimisation

}