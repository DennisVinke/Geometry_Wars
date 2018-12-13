#pragma once
#include <glm/glm.hpp>

#include "Component.h"


class MovementComponent : public Component
{
private:
	glm::vec2 position = glm::vec2(0,0);
	glm::vec2 constMove = glm::vec2(0, 0);
public:
	MovementComponent();
	~MovementComponent();

	void execute() override;
	void init() override;

	void doMovement(glm::vec2);
	void constantMovement();
	void setConstantMovement(glm::vec2);

};

