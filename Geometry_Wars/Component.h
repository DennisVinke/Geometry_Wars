#pragma once
#include "Entity.h"

// hoi dennis


class Component
{
public:
	Component();
	~Component();
	virtual void init() = 0;
	virtual void execute() = 0;
	virtual void toString() = 0;
	
	Entity * entity;
	bool remove = false;
	int id = -1;
};

