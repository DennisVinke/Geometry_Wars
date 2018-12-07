#pragma once
#include "Entity.h"

// hoi dennis


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

