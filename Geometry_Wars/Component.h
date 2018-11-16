#pragma once
class Component
{
public:
	Component();
	~Component();

	virtual void execute() = 0;
private:
	void updateHealth();
	
};

