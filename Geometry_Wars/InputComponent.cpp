#include "InputComponent.h"
#include "MovementComponent.h"
#include "EntityManager.h"

InputComponent::InputComponent()
{
	for (uint8_t i = 0; i < maxActions;i++) {
		controllers[i] = new ActionController();
	}
}

InputComponent::~InputComponent()
{
	for (uint8_t i = 0; i < maxActions;i++) {
		controllers[i]->~ActionController();
	}
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

void InputComponent::addActionController() {
//	controllers[index] = new ActionController();
}

ActionController& InputComponent::getActionController(uint8_t idx) {
	assert(idx<=maxActions);
	return * (controllers[idx]);
}

void InputComponent::print() {
	std::cout << "InputComponent" << std::endl;
}

void InputComponent::removeActionController(uint8_t idx) {
	controllers[idx]->~ActionController();
}

void InputComponent::executeInput() {
	if (entity->hasComponent<MovementComponent>()) {
		entity->getComponent<MovementComponent>()->doMovement(glm::vec2(getActionController(0).getValue(), getActionController(1).getValue()));
	}
	//if (entity->hasComponent<MovementComponent>()) {
	// entity->getComponent<MovementComponent>()->getLocation();
	//}
}