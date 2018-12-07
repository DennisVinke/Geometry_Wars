#pragma once
#include "Entity.h"

// hoi Dennis
// nog een poging

class Component
{
public:
	Component()=delete;
	Component(Entity&);
	~Component();

	virtual void init() = 0;
	virtual void execute() = 0;

private: 
	Entity& entity;

};

