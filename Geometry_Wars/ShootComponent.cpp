#include "ShootComponent.h"

#include "GameObjectSpawner.h"
#include "MovementComponent.h"
#include "EntityManager.h"


ShootComponent::ShootComponent(GameObjectSpawner& bullet_spwnr):Component(),bullet_spawner(bullet_spwnr) {

}

void ShootComponent::execute() {}

void ShootComponent::init() {}

void ShootComponent::print() {}

void ShootComponent::shoot(glm::vec2 clickPosition, float delta_time) {
	current_time += delta_time;
	if (current_time > weapons[current_gun]->cooldown) {
		current_time=0;
		glm::vec2 position = entity->getComponent<MovementComponent>()->getLocation();
		weapons[current_gun]->gunBehaviour(bullet_spawner, position, clickPosition);
	}
}

void ShootComponent::setBulletColor(int r, int  g, int  b, int  a) {

}
/*
void ShootComponent::setBulletBehaviour() {

}*/

void ShootComponent::setWeapon(Weapon * weapon) {
	weapons[current_gun] = weapon;
}

void ShootComponent::next_weapon() {
	current_gun = (current_gun + 1) % 3;
	current_time = weapons[current_gun]->cooldown;
}

void ShootComponent::set_mask(int new_mask) {
	weapons[current_gun]->set_mask(new_mask);
}