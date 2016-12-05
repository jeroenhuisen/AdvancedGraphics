#pragma once
#include <set>
#include "movementController.h"


class ButtonHandler {
private:
	std::set<int> buttons;
	MovementController* movement;
public:
	ButtonHandler(MovementController* movement);
	void addButton(int button);
	void removeButton(int button);
	void updateKeys();
};