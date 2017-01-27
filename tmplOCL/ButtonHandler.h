#pragma once
#include <set>
#include "movementController.h"


class ButtonHandler {
private:
	std::set<int> buttons;
	MovementController* movement;
public:
	ButtonHandler(MovementController* movement);
	void addButton(const int button);
	void removeButton(const int button);
	void updateKeys();
};