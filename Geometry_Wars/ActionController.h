#pragma once
#include <cstdint>

class ActionController {
public:
	ActionController();
	void add(float state);
	float getValue();
private:
	float value;
	uint8_t tag;
};