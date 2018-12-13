#include "MovementComponent.h"



MovementComponent::MovementComponent()
{
}


MovementComponent::~MovementComponent()
{
}

void MovementComponent::execute() {
	constantMovement();
}


void MovementComponent::init() {
	position = glm::vec2(0, 0);
}


void MovementComponent::doMovement(glm::vec2 move) {
	position += move;
}

void MovementComponent::constantMovement() {
	doMovement(constMove);
}

void MovementComponent::setConstantMovement(glm::vec2 value) {
	constMove = value;
}
