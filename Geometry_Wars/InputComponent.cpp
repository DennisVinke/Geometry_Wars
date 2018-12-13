#include "InputComponent.h"



InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::execute() {
	constantMovement();
}


void InputComponent::init() {
	position = glm::vec2(0, 0);
}


void InputComponent::doMovement(glm::vec2 move) {
	position += move;
}

void InputComponent::constantMovement() {
	doMovement(constMove);
}

void InputComponent::setConstantMovement(glm::vec2 value) {
	constMove = value;
}
