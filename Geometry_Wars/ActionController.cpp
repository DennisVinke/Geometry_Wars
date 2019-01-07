#include "ActionController.h"
#include <algorithm>

ActionController::ActionController() :value(0.0f) {}

void ActionController::add(float state) {
	value += state;
}
float ActionController::getValue() {
	return std::clamp(value, -1.0f, 1.0f);
}
