#pragma once
#include "GameObject.h"
class Component
{
public:
	Component();
	~Component();

	virtual void init(GameObject *) = 0;
	virtual void execute() = 0;
	
};

