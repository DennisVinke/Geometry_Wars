#pragma once
#include <glm/glm.hpp>

#include "engine/Component.h"

/*! \file MovementComponent.h
	\brief A component responsible for the movement of an Entity
*/


/// Components that gives entities ability to move
class MovementComponent : public Component
{
private:
	glm::vec2 startPosition = glm::vec2(0, 0); //should be removed
	glm::vec2 position = glm::vec2(0,0); //should be removed
	glm::vec2 constMove = glm::vec2(0, 0);
public:

    /// Constructor of MovementComponent
	MovementComponent();
	
    /// brief Constructor of MovementComponent
    /// param constMovement initial vector of speed an entity will be moved per update
	MovementComponent(glm::vec2);

    /// Destructor of MovementComponent
	~MovementComponent();

    /// Override function to execute component logic every update
	void execute() override;
	
    /// Override function to init component when created. Used when old components are reused. If created please use the constructor
    void init() override;
	
    /// Override function to print the name of the component to the console. Only used for testing!
    void print() override;

    /// Adds the vec2 to the entities current position
    /// \param move the position the object should move
	void doMovement(glm::vec2);

    /// Adds the vec2 to the entities current position
    /// \param xpos the position the object should move in the X - axis
    /// \param ypos the position the object should move in the Y - axis
	void doMovement(int x, int y);

    /// Adds the constantMovement vector to the entities current position
	void constantMovement();

    /// setConstantMovement(glm::vec2 newMovement)
    /// \brief Change the constantMovement vector with a new value;
    /// \param newMovement the new constantMovement value
	void setConstantMovement(glm::vec2);

    /// setConstantMovement(glm::vec2 newMovement)
    /// \brief Change the constantMovement vector with a new value;
    /// \param newMovement the new constantMovement value
	void setConstantMovement(int x, int y);

    /// returns x the y value the new constantMovement vector should change to
	glm::vec2 getLocation();

    /// sets the position 
	void setPosition(glm::vec2);


    /// handles input
	void handleInput();


};

