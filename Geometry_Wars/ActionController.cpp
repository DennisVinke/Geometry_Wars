#include "ActionController.h"
#include <algorithm>

ActionController::ActionController() :value(0.0f) {}

void ActionController::add(float state) {
	value += state;
}
float ActionController::getValue() {
	return std::clamp(value, -1.0f, 1.0f);
}

void ActionController::setMousePosition(uint16_t _x, uint16_t _y)
{
	x = _x;
	y = _y;
}

glm::vec2 ActionController::getClickedPosition() {
	return glm::vec2(x, y);
}
