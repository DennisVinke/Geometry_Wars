#include "ShootComponent.h"

#include "GameObjectSpawner.h"
#include "MovementComponent.h"
#include "EntityManager.h"

ShootComponent::ShootComponent(GameObjectSpawner& bullet_spwnr):Component(),bullet_spawner(bullet_spwnr) {

}

void ShootComponent::execute() {}

void ShootComponent::init() {}

void ShootComponent::print() {}

void ShootComponent::shoot(glm::vec2 clickPosition) {
	glm::vec2 position = entity->getComponent<MovementComponent>()->getLocation();
	weapons[current_gun]->gunBehaviour(bullet_spawner,position,clickPosition);
}

void ShootComponent::setBulletColor(int r, int  g, int  b, int  a) {

}
/*
void ShootComponent::setBulletBehaviour() {

}*/

void ShootComponent::setWeapon(Weapon * weapon) {

}

void ShootComponent::next_weapon() {
	current_gun = (current_gun + 1) % 3;
}