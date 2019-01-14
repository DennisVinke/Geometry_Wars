#include "MovementComponent.h"
#include "InputComponent.h"
#include "RenderComponent.h"


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

 
void MovementComponent::print() {
	std::cout << "MovementComponent!" << std::endl;
}


void MovementComponent::doMovement(glm::vec2 move) {
	position += move;
	if (position.x > 1280 || position.x<0)setConstantMovement(-constMove.x , constMove.y);//position.x = 0;//startPosition.x;
	if (position.y > 720 || position.y<0)setConstantMovement(constMove.x, -constMove.y);//position.y = 0;//startPosition.y;
	//if (position.x < 0)//position.x = 1280;
	//if (position.y < 0)//position.y - 720;
	//std::cout << position.x << ":" << position.y << std::endl;
}

void MovementComponent::doMovement(int x, int y) {
	position.x += x;
	position.y += y;
	if (position.x > 1280 || position.x < 0) position.x *= -1;
	if (position.y > 720 || position.y < 0) position.y *= -1;
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

void MovementComponent::handleInput() {
}