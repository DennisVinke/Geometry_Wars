#pragma once
#include "engine/Component.h"

/*! \file HealthComponent.h
	\brief A component responsible for the Health of an Entity which determines if an entity in the game is still alive
*/

/// class HealthComponent: A component responsible for the Health of an Entity which determines if an entity in the game is still alive.
/*
 *	This class is responsible for managing the health and lifespan of a component
 */
class HealthComponent : public Component
{

public:
	/// HealthComponent
	/*
	* Constructor of HealthComponent
	*/
	HealthComponent();

	~HealthComponent();
	
	///  init()
	/*
	* Override function to init component when created. Used when old components are reused. If created please use the constructor
	*/
	void init() override;

	/// execute()
	/*
	* Override function to execute component logic every update. Looks if the entity is still alive
	*/
	void execute() override;

	/// print()
	/*
	* Override function to print the name of the component to the console. Only used for testing!
	*/
	void print() override;

	/// updateHealth(int damage)
	/*	reduce the current health with given damage
	*	@param damage the value currentHealth should be changed with. Can be negative for a heal
	*/
	void updateHealth(int damage);
	
	/// setCurrentHealth(int newHealth)
	/*	sets the health of an entity to the given value
	*	@param newHealth, the value the currentHealth should be
	*/
	void setCurrentHealth(int currentHealth);
	
	///	setMaxHealth(int maxHealth)
	/*	 
	*	sets the maximum health value an entity can have to a new value
	*	@param maxHealth new value for maxHealth
	*/
	void setMaxHealth(int);
	
	/// isAlive()
	/* 
	*	tells the game if this component should be removed	
	*/
	bool isAlive();
private:
	int currentHealth;
	int maxHealth;
};

