#pragma once
#include <glm/glm.hpp>

#include "Component.h"


class MovementComponent : public Component
{
private:
	glm::vec2 startPosition = glm::vec2(0, 0);
	glm::vec2 position = glm::vec2(0,0);
	glm::vec2 constMove = glm::vec2(0, 0);
public:
	MovementComponent();
	MovementComponent(glm::vec2);
	~MovementComponent();

	void execute() override;
	void init() override;
	void print() override;

	void doMovement(glm::vec2);
	void doMovement(int x, int y);
	void constantMovement();
	void setConstantMovement(glm::vec2);
	void setConstantMovement(int x, int y);
	glm::vec2 getLocation();
};

