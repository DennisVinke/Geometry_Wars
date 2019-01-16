#pragma once
#include <cstdint>
#include <utility>
#include <map>
#include <vector>

#include "engine/ActionController.h"

#include "components/InputComponent.h"


#define MOUSEKEYOFFSET 512
#define SDL_MOUSEBUTTON_TYPES 5

/// class InputManager: Class that adds an abstract layer to the SDL input and manages InputComponents.
/**
 *  The InputManager class allows ActionControllers to be connected with SDL input
 *	The InputManager updates all registered interaction and notifices the connnected ActionControllers 
 *	InputControllers can register themselves and remove themselves so they can be updated
 */
class InputManager {
public:
	InputManager() {}
	void onKeyDown(uint32_t key, bool repeated);
	void onKeyUp(uint32_t key, bool repeated);
	void onMouseDown(uint32_t button, uint8_t numOfClicks);
	void onMouseUp(uint32_t button,  uint8_t numOfClicks);
	void onMouseMove(uint32_t mouseX, uint32_t mouseY, uint32_t mouseDeltaX, uint32_t mouseDeltaY);

	void addKeyControl(uint32_t key, ActionController& controller, float weight);
	void addMouseControl(uint32_t button, ActionController& controller, float weight);

	void addInputComponent(InputComponent*);
	void removeInputComponent(InputComponent*);
	void executeInput(float delta_time);
	void update(float delta_time);

private:
	std::map<uint32_t, std::vector<std::pair<float, ActionController&>>> inputActions;
	std::vector<InputComponent *> inputComponents;

	void updateInput(uint32_t input, float dir, bool repeated);
};