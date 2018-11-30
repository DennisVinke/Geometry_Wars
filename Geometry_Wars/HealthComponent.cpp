#include "HealthComponent.h"



HealthComponent::HealthComponent()
{
}


HealthComponent::~HealthComponent()
{
}

void HealthComponent::execute() {
	//if()
}


void HealthComponent::init(GameObject * gameObject) {
	

}

void HealthComponent::receivedDamage(int damage) {
	health -= damage;
}
