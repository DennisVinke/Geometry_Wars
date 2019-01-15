#pragma once
#include "engine/Component.h"

/*! \file HealthComponent.h
	\brief A component responsible for the Health of an Entity which determines if an entity in the game is still alive
*/

/*! \fn HealthComponent()
	\brief Constructor of HealthComponent
*/

/*! \fn ~HealthComponent()
	\brief Destructor of HealthComponent
*/

/*! \fn execute()
	\brief Override function to execute component logic every update. Looks if the entity is still alive
*/

/*! \fn init()
	\brief Override function to init component when created. Used when old components are reused. If created please use the constructor
*/

/*! \fn print()
	\brief Override function to print the name of the component to the console. Only used for testing!
*/

/*! \fn isAlive()
	\brief tells the game if this component should be removed

	\return bool health > 0
*/

/*! \fn setCurrentHealth(int newHealth)
	\brief sets the health of an entity to the given value

	\param newHealth, the value the currentHealth should be
*/

/*! \fn setMaxHealth(int maxHealth)
	\brief sets the maximum health value an entity can have to a new value

	\param maxHealth new value for maxHealth
*/

/*! \fn updateHealth(int damage)
	\brief reduce the current health with given damage

	\param damage the value currentHealth should be changed with. Can be negative for a heal
*/

/*! \var int currentHealth
	\brief Contains the current health value of an entity
*/

/*! \var int maxHealth
	\brief Contains the maximum health value an entity can have. currentHealt can be bigger than maxHealth if maxHealth is set to a value lower than currentHealth
*/
class HealthComponent : public Component
{

public:
	HealthComponent();// = delete;
	//HealthComponent(Entity& entity);

	~HealthComponent();
	
	void init() override;
	void execute() override;
	
	void print();
	void updateHealth(int damage);
	void setCurrentHealth(int currentHealth);
	void setMaxHealth(int);
	bool isAlive();
private:
	int currentHealth;
	int maxHealth;
};

