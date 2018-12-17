#pragma once
#include <glm/glm.hpp>

#include "Component.h"

/*! \file MovementComponent.h
	\brief A component responsible for the movement of an Entity
*/

/*! \fn MovementComponent()
	\brief Constructor of MovementComponent
*/

/*! \fn MovementComponent(glm::vec2 constMovement)
	\brief Constructor of MovementComponent

	\param constMovement initial vector of speed an entity will be moved per update
*/

/*! \fn ~MovementComponent()
	\brief Destructor of MovementComponent
*/

/*! \fn execute()
	\brief Override function to execute component logic every update
*/

/*! \fn init()
	\brief Override function to init component when created. Used when old components are reused. If created please use the constructor
*/

/*! \fn print()
	\brief Override function to print the name of the component to the console. Only used for testing!
*/

/*! \fn doMovement(glm::vec2 move)
	\brief Adds the vec2 to the entities current position

	\param move the position the object should move
*/

/*! \fn doMovement(int xpos, int ypos)
	\brief Adds the vec2 to the entities current position

	\param xpos the position the object should move in the X-axis
	\param ypos the position the object should move in the Y-axis
*/

/*! \fn constantMovement()
	\brief Adds the constantMovement vector to the entities current position
*/

/*! \fn setConstantMovement(glm::vec2 newMovement)
	\brief Change the constantMovement vector with a new value;

	\param newMovement the new constantMovement value	
*/

/*! \fn setConstantMovement(int x, int y)
	\brief Change the constantMovement vector with a new value;

	\param x the x value the new constantMovement vector should change to
	\param y the y value the new constantMovement vector should change to
*/

/*! \fn getLocation()
	\brief returns;

	\param y the y value the new constantMovement vector should change to
*/

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

