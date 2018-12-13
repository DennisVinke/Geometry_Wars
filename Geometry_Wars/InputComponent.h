#pragma once
#include <glm/glm.hpp>

#include "Component.h"


class InputComponent : public Component
{
private:
	glm::vec2 position = glm::vec2(0,0);
	glm::vec2 constMove = glm::vec2(0, 0);
public:
	InputComponent();
	~InputComponent();

	void execute() override;
	void init() override;

	void doMovement(glm::vec2);
	void constantMovement();
	void setConstantMovement(glm::vec2);

};

