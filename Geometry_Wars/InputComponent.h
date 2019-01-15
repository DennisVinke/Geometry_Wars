#pragma once
#include <glm/glm.hpp>
#include <array>

#include "Component.h"
#include "ActionController.h"

constexpr auto maxActions = 10;
/*For ActionArray :
	0 horizontal
	1 vertical
	2 left click
	3 right click
	4 toggle
*/
using ActionArray = std::array <ActionController *, maxActions>;

class InputComponent : public Component
{
private:
	glm::vec2 position = glm::vec2(0,0);
	glm::vec2 constMove = glm::vec2(0, 0);
	ActionArray controllers;
public:
	InputComponent();
	~InputComponent();

	void execute() override;
	void init() override;
	void print() override;

	void doMovement(glm::vec2);
	void constantMovement();
	void setConstantMovement(glm::vec2);

	void addActionController();
	ActionController& getActionController(uint8_t index);
	void removeActionController(uint8_t idx);

	void executeInput(float delta_time);
	//void clearControllers();
};

