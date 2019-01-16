#include "components/InputComponent.h"
#include "components/MovementComponent.h"
#include "components/ShootComponent.h"
#include "engine/EntityManager.h"

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
}


void InputComponent::init() {
}


ActionController& InputComponent::getActionController(uint8_t idx) {
	assert(idx<=maxActions);
	return * (controllers[idx]);
}

void InputComponent::print() {
	std::cout << "InputComponent" << std::endl;
}

void InputComponent::executeInput(float delta_time) {
	if (entity->hasComponent<MovementComponent>()) {
		entity->getComponent<MovementComponent>()->doMovement(glm::vec2(getActionController(0).getValue()*3, getActionController(1).getValue()*3));
	}
	if (getActionController(2).getValue() >= 1) {
		if (entity->hasComponent<ShootComponent>()) {
			entity->getComponent<ShootComponent>()->shoot(getActionController(2).getClickedPosition(),delta_time);
		}

		if (getActionController(4).getValue() >= 1) {
			entity->getComponent<ShootComponent>()->next_weapon();
		}
		
	}
}