#pragma once
#include <cstdint>

#include <glm/glm.hpp>


class ActionController {
public:
	ActionController();
	void add(float state);
	float getValue();
	void setMousePosition(uint16_t, uint16_t);
	glm::vec2 getClickedPosition();
private:
	float value;
	uint8_t tag;
	uint16_t x,y;
};