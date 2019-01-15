#pragma once

#include "engine/Entity.h"


/*! \file Component.h
	\brief Base class for all the components used by the game
*/

/*! \fn Component()
	\brief Constructor of Component
*/

/*! \fn Component(glm::vec2 constMovement)
	\brief Constructor of Component

	\param constMovement initial vector of speed an entity will be moved per update
*/

/*! \fn ~MovementComponent()
	\brief Destructor of MovementComponent
*/

/*! \fn execute()
	\brief virtual function to execute component logic every update
*/

/*! \fn init()
	\brief virtual function to init component when created. Used when old components are reused. If created please use the constructor
*/

/*! \fn print()
	\brief virtual function to print the name of the component to the console. Only used for testing!
*/

/*! \var Entity * entity
	\brief contains a reference to the entity the component is linked with
*/

/*! \var int id
	\brief contains the unique id number of the componentType.
*/

class Component
{
	//Extra abstractie voor objecten die alleen data bevatten zodat ze niet meegenomen worden in de execute functie?
public:
	Component();
	~Component();
	virtual void init() = 0;
	virtual void execute() = 0;
	virtual void print() = 0;
	
	Entity * entity;
	bool remove = false; //should not be used anymore?
	int id = -1;
};

