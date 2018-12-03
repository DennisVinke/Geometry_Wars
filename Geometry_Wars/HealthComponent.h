#pragma once
#include "Component.h"

class HealthComponent : protected Component
{
	friend class ComponentManager;
public:
	HealthComponent() = delete;
	HealthComponent(Entity& entity);

	~HealthComponent();
	
	void init() override;
	void execute() override;
	
	void updateHealth(int damage);
	void setCurrentHealth(int currentHealth);
	void setMaxHealth(int);
	bool isAlive();
private:
	int currentHealth;
	int maxHealth;
};

