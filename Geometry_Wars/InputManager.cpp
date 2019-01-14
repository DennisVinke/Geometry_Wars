#include "InputManager.h"
#include <algorithm>

void InputManager::onKeyDown(uint32_t key, bool repeated) {
	updateInput(key, 1.0f, repeated);
}

void InputManager::onKeyUp(uint32_t key, bool repeated) {
	updateInput(key, -1.0f, repeated);
}
void InputManager::onMouseDown(uint32_t button, uint8_t numOfClicks) {
	updateInput(MOUSEKEYOFFSET+button, 1.0f, false);
}
void InputManager::onMouseUp(uint32_t button, uint8_t numOfClicks) {
	updateInput(MOUSEKEYOFFSET+button, -1.0f, false);
}
void InputManager::onMouseMove(uint32_t mouseX, uint32_t mouseY, uint32_t mouseDeltaX, uint32_t mouseDeltaY) {
	for (auto i = 1; i < SDL_MOUSEBUTTON_TYPES;i++) {
		for (auto pair : inputActions[MOUSEKEYOFFSET+i]) {
			pair.second.setMousePosition(mouseX, mouseY);
		}
	}
}

void InputManager::addKeyControl(uint32_t key, ActionController& controller, float weight) {
	inputActions[key].emplace_back(std::pair<float, ActionController&>(weight, controller));
}

void InputManager::addMouseControl(uint32_t button, ActionController& controller, float weight) {
	inputActions[MOUSEKEYOFFSET+button].emplace_back(std::pair<float, ActionController&>(weight, controller));
}

void InputManager::updateInput(uint32_t keyCode, float dir, bool repeated) {
	if (repeated) {
		return;
	}

	for (auto pair : inputActions[keyCode]) {
		pair.second.add(pair.first * dir);
	}
}

void InputManager::addInputComponent(InputComponent* input) {
	inputComponents.emplace_back(input);
}

void InputManager::removeInputComponent(InputComponent* input) {
//	inputComponents.erase(std::remove(inputComponents.begin(), inputComponents.end(), input),inputComponents.end());
}

void InputManager::executeInput(float delta_time) {
	for (auto component : inputComponents) {
		component->executeInput(delta_time);
	}
}

void InputManager::update(float delta_time) {
	executeInput(delta_time);
}