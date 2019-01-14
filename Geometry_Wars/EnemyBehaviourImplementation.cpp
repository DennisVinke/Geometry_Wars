#include "EnemyBehaviour.h"
#include "math_utils.h"

glm::vec2 Chaser::update(glm::vec2 current_position, glm::vec2 player_position) {
	glm::vec2 position = current_position;
	glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
	update_position *= speed;
	return update_position;
}

glm::vec2 Random::update(glm::vec2 position, glm::vec2 player_position) {
	glm::vec2 random_direction(random(-1, 1), random(-1, 1));
	random_direction *= speed;
	return random_direction;
}

glm::vec2 ChaserWhenNear::update(glm::vec2 position, glm::vec2 player_position) {
	if (glm::distance(position, player_position) < min_chase_distance)
	{
		glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
		update_position *= speed;
		return update_position;
	}
	return glm::vec2(0, 0); 
}

glm::vec2 Shooting::update(glm::vec2 position, glm::vec2 player_position) { 
	glm::vec2 update_position = glm::vec2((player_position - position) / glm::distance(player_position, position));
	update_position *= speed;

	return update_position;
}