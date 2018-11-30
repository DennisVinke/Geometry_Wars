#pragma once
#include "Component.h"
class HealthComponent :
	protected Component
{
public:
	HealthComponent();
	~HealthComponent();
	
	void init(GameObject *) override;
	void execute() override;
	
private:
	int * currentHealth;
	int maxHealth;
};

