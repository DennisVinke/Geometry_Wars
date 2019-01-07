#pragma once

class ActionController {
public:
	ActionController();
	void add(float state);
	float getValue();
private:
	float value;
};