#pragma once
#include "Component.h"
class HealthComponent :
	protected Component
{
public:
	HealthComponent();
	~HealthComponent();
	
	void execute() override;

private:
	int * currentHealth;
	int maxHealth;
};

