#pragma once
#include <cstdint>
#include <utility>
#include <map>
#include <vector>
#include "ActionController.h"

#define MOUSEKEYOFFSET 512
#define SDL_MOUSEBUTTON_TYPES 5
/*
	@Aart gaan we hier nog een interface voor schrijven of vind je het wel prima zo?
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

private:
	std::map<uint32_t, std::vector<std::pair<float, ActionController&>>> inputActions;
	void updateInput(uint32_t input, float dir, bool repeated);
};