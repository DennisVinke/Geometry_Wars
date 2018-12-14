#include "MovementComponent.h"



MovementComponent::MovementComponent()
{
}

MovementComponent::MovementComponent(glm::vec2 startPos):startPosition(startPos)
{
	position = startPos;
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


void MovementComponent::toString() {
	std::cout << "MovementComponent!" << std::endl;
}


void MovementComponent::doMovement(glm::vec2 move) {
	position += move;
	if (position.x > 600)position.x = startPosition.x;
	if (position.y > 600)position.y = startPosition.y;
	//std::cout << position.x << ":" << position.y << std::endl;
}

void MovementComponent::doMovement(int x, int y) {
	position.x += x;
	position.y += y;
	if (position.x > 600)position.x = startPosition.x;
	if (position.y > 600)position.y = startPosition.x;
	//std::cout << position.x << ":"<<position.y<<std::endl;

}

void MovementComponent::constantMovement() {
	doMovement(constMove);
}

void MovementComponent::setConstantMovement(glm::vec2 value) {
	constMove = value;
}

void MovementComponent::setConstantMovement(int x, int y) {
	constMove.x = x;
	constMove.y = y;
}

glm::vec2 MovementComponent::getLocation() {
	return position;
}
