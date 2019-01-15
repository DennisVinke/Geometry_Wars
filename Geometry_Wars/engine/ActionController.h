#pragma once
#include <cstdint>

#include <glm/glm.hpp>

/// class ActionController: Handles actions based on Events given by the window
/*
 *	This class is responsible for handling the input abstracted by the InputManager
 *	The ActionController can be set active (positive and negative)
 *	
 */
class ActionController {
public:
	ActionController();
	/// add(float state)
	/*
	*	Activate or deactive active state
	*/
	void add(float state);
	float getValue();
	void setMousePosition(uint16_t, uint16_t);
	glm::vec2 getClickedPosition();
private:
	float value;
	uint8_t tag;
	uint16_t x,y;
};