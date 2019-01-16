#pragma once

#include <glm/glm.hpp>
#include "engine/Component.h"
#include "content/Weapon.h"

class GameObjectSpawner;

/// class ShootComponent: A component responsible for the shooting abilities of an entity
/**
*	Gives entities the ability to shoot and gives the required data when a shot needs to be done
*	to the GameObjectSpawner so the bullet can actually be created
*	Contains three different guns which can be used 
 */
class ShootComponent : public Component 
{

public:

	/// Constructor
		/**
		* Constructor to initialize InputComponent
		* @param reference to the GameObjectSpawner
		*/
	ShootComponent(GameObjectSpawner& bullet_spwner);
	~ShootComponent();

	void execute() override;
	void init() override;
	void print() override;

	/// shoot
	/**
	*	Test if the component is allowed to shoot
	*	if yes then calculates the trajectory of the bullet based on the current weapon equiped
	*	and sends a request to the GameObjectSpawner to create the desired bullet
	*	@param glm::vec2 position the bullets is aimed at.
	*	@param float time sinds last update
	*/
	void shoot(glm::vec2 clickedPosition, float delta_time);

	/// setBulletColor(int r, int g, int b, int a)
	/**
	*	Sets the color of the bullet to the desired values
	*/


	void setBulletColor(int r, int g, int b, int a);

	/// setWeapon(Weapon * weapon)
	/**
	*	changes Current Weapon to the given weapon given as argument
	*	@param new Weapon. Make sure the pointer is a derived class instead of base class.
	*/
	void setWeapon(Weapon * weapon);


	/// next_weapon()
	/**
	*	Switches to next wapen.
	*/
	void next_weapon();


	///	set_mask(int new_mask)
	/**
	*	Set collision type to bullet or enemybullet
	*/

	void set_mask(int new_mask);


private:
	GameObjectSpawner& bullet_spawner;
	int current_gun = 0;
	std::array<Weapon*, 3> weapons{new SingleShotGun(), new DoubleShotGun(), new TripleShotGun()};
	int lastFired;
	float current_time = 0;

};