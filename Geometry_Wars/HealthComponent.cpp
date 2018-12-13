#include "HealthComponent.h"
#include <iostream>


HealthComponent::HealthComponent() : Component()
{

}

HealthComponent::~HealthComponent()
{
}


void HealthComponent::execute() {
	//if()
}


void HealthComponent::init() {
	setMaxHealth(100);
	setCurrentHealth(maxHealth);
}

void HealthComponent::updateHealth(int damage) {

}

void HealthComponent::setCurrentHealth(int currentHealth) {

}


void HealthComponent::setMaxHealth(int newMaxHealth) {
	maxHealth = newMaxHealth;
}

bool HealthComponent::isAlive() {
	return currentHealth <= 0;
}

void HealthComponent::toString() {
	std::cout << "HealthComponent!" << std::endl;
}
/*
void HealthComponent::receivedDamage(int damage) {
	health -= damage;
}*/
