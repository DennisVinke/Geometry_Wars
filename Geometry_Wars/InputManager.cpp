#include "InputManager.h"

void InputManager::onKeyDown(uint32_t key, bool repeated) {
	updateInput(key, 1.0f, repeated);
}

void InputManager::onKeyUp(uint32_t key, bool repeated) {
	updateInput(key, -1.0f, repeated);
}
void InputManager::onMouseDown(uint32_t button, uint8_t numOfClicks) {
	updateInput(button, 1.0f, false);
}
void InputManager::onMouseUp(uint32_t button, uint8_t numOfClicks) {
	updateInput(button, -1.0f, false);
}
void InputManager::onMouseMove(uint32_t mouseX, uint32_t mouseY, uint32_t mouseDeltaX, uint32_t mouseDeltaY) {

}

void InputManager::addKeyControl(uint32_t key, ActionController& controller, float weight) {
	inputActions[key].emplace_back(std::pair<float, ActionController&>(weight, controller));
}

void InputManager::addMouseControl(uint32_t button, ActionController& controller, float weight) {
	inputActions[button].emplace_back(std::pair<float, ActionController&>(weight, controller));
}

void InputManager::updateInput(uint32_t keyCode, float dir, bool repeated) {
	if (repeated) {
		return;
	}

	for (auto pair : inputActions[keyCode]) {
		pair.second.add(pair.first * dir);
	}
}