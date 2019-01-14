#include "Weapon.h"
#include "GameObjectSpawner.h"

void SingleShotGun::gunBehaviour(GameObjectSpawner& spawn, glm::vec2 spawn_position, glm::vec2 click_position) {
		speed = glm::vec2((click_position - spawn_position) / glm::distance(click_position, spawn_position));
		spawn.spawn_bullet(this, spawn_position);
	}


void DoubleShotGun:: gunBehaviour(GameObjectSpawner& spawn, glm::vec2 spawn_position, glm::vec2 click_position) {
		speed = glm::vec2((click_position - spawn_position) / glm::distance(click_position, spawn_position));
		spawn.spawn_bullet(this, glm::vec2(spawn_position.x-10, spawn_position.y));
		spawn.spawn_bullet(this, glm::vec2(spawn_position.x + 10, spawn_position.y));
}

void TripleShotGun::gunBehaviour(GameObjectSpawner& spawn, glm::vec2 spawn_position, glm::vec2 click_position) {
		speed = glm::vec2((click_position - spawn_position) / glm::distance(click_position, spawn_position));
		spawn.spawn_bullet(this, spawn_position);
		speed.x += .5;
		spawn.spawn_bullet(this, spawn_position);
		speed.x *= -1;
		spawn.spawn_bullet(this, spawn_position);
}

