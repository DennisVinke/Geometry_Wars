#include "content/EnemyBehaviour.h"
#include "utility/random.h"
#include "components/ShootComponent.h"
#include "engine/EntityManager.h"





glm::vec2 Chaser::update(Entity * enemy, glm::vec2 player_position) {
	glm::vec2 position = enemy->getComponent<MovementComponent>()->getLocation();
	glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
	update_position *= speed;
	return update_position;
}

glm::vec2 Random::update(Entity * enemy, glm::vec2 player_position) {
	glm::vec2 random_direction(random(-1, 1), random(-1, 1));
	random_direction *= speed;
	return random_direction;
}

glm::vec2 ChaserWhenNear::update(Entity * enemy, glm::vec2 player_position) {
	glm::vec2 position = enemy->getComponent<MovementComponent>()->getLocation();
	if (glm::distance(position, player_position) < min_chase_distance)
	{
		glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
		update_position *= speed;
		return update_position;
	}
	return glm::vec2(0, 0); 
}

glm::vec2 Shooting::update(Entity * enemy, glm::vec2 player_position) {
	glm::vec2 position = enemy->getComponent<MovementComponent>()->getLocation();
	glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
	update_position *= speed;
	enemy->getComponent<ShootComponent>()->shoot(update_position,0.016);
	return update_position;
}