#pragma once
#include "Entity.h"

// hoi dennis


class Component
{
	//Extra abstractie voor objecten die alleen data bevatten zodat ze niet meegenomen worden in de execute functie?
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

