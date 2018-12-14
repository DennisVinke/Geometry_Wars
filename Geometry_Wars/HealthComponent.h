#pragma once
#include "Component.h"

class HealthComponent : public Component
{

public:
	HealthComponent();// = delete;
	//HealthComponent(Entity& entity);

	~HealthComponent();
	
	void init() override;
	void execute() override;
	
	void print();
	void updateHealth(int damage);
	void setCurrentHealth(int currentHealth);
	void setMaxHealth(int);
	bool isAlive();
private:
	int currentHealth;
	int maxHealth;
};

