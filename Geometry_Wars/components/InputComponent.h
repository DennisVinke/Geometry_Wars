#pragma once
#include <glm/glm.hpp>
#include <array>

#include "engine/Component.h"
#include "engine/ActionController.h"

constexpr auto maxActions = 10;
/*For ActionArray :
	0 horizontal
	1 vertical
	2 left click
	3 right click
	4 toggle
*/
using ActionArray = std::array <ActionController *, maxActions>;

/// class InputComponent: A component responsible for managing the user input connected to an entity
/**
 *	This class is responsible for the user input connected to an entity
 *	This is done by having 10 possible ActionControllers to which buttons and actions can be matched.
 *	For Geometry_Wars only 4 ActionControllers are used.
 */
class InputComponent : public Component
{
private:
	ActionArray controllers;
public:
	/// Constructor
	/**
	* Constructor to initialize InputComponent
	*/
	InputComponent();
	~InputComponent();

	/// execute()
	/**
	* Override function to execute component logic every update. Looks if the entity is still alive
	*/
	void execute() override;
	
	///  init()
	/**
	* Override function to init component when created. Used when old components are reused. If created please use the constructor
	*/
	void init() override;

	/// print()
	/**
	* Override function to print the name of the component to the console. Only used for testing!
	*/
	void print() override;

	/// ActionController& getActionController(uint8_t index)
	/**
	* Request one of the available ActionControllers linked to this component
	* @param index of the requested ActionController. Needs to be smaller than maxActions
	* @return The requested ActionController
	*/
	ActionController& getActionController(uint8_t index);
	
	/// executeInput(float delta_time)
	/**
	* Translates the ActionController values to actions done by the entity
	* @param the time between frames to make updates more consistant
	*/
	void executeInput(float delta_time);
};

