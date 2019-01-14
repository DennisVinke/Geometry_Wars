#pragma once
#include "MovementComponent.h"
#include "Shape.h"

struct EnemyBehaviour {
public:
	int bulletBehaviour = 0;
	int red = 125;
	int green = 125;
	int blue = 125;
	int alpha = 125;
	glm::vec2 speed = glm::vec2(1, 1);
	int size = 10;
	int cooldown;
	float movement_speed;
	std::vector<glm::vec2> shape;
	virtual glm::vec2 update(Entity *, glm::vec2 player_position) = 0;
	MovementComponent * current_position;
	glm::vec2 player_position;
};

struct Chaser :EnemyBehaviour {
public:
	inline Chaser() {
		red = 100;
		blue = 100;
		green = 100;
		alpha = 190;
		speed = glm::vec2(5, 5);
	}
	glm::vec2 update(Entity *, glm::vec2 player_position) override;
};

struct Random :EnemyBehaviour {
	glm::vec2 update(Entity *, glm::vec2 player_position) override;
};
struct ChaserWhenNear :EnemyBehaviour {
	int min_chase_distance = 100;
	glm::vec2 update(Entity *, glm::vec2 player_position) override;
};

struct Shooting : Chaser {
	glm::vec2 shoot_speed =  glm::vec2(1, 1);
	glm::vec2 update(Entity *, glm::vec2 player_position);
	//inline glm::vec2 get_shoot_vector() {
	//	return shoot_vector*shoot_speed;
	//}
};