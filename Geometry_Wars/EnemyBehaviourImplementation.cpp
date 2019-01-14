#include "EnemyBehaviour.h"

void Chaser::update() {
	glm::vec2 position = current_position->getLocation();
	glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
}

void Random::update() {}
void ChaserWhenNear::update() {}
void Shooting::update() {}