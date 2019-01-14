#pragma once
#include "MovementComponent.h"
#include "Shape.h"

struct EnemyBehaviour {
public:
	int bulletBehaviour = 0;
	int red, green, blue, alpha = 255;
	glm::vec2 speed = glm::vec2(0, 0);
	int size = 1;
	int cooldown;
	float movement_speed;
	virtual void update() = 0;
	MovementComponent * current_position;
	glm::vec2 player_position;
};

struct Chaser :EnemyBehaviour {
	void update() override;
};

struct Random :EnemyBehaviour {
	void update() override;
};
struct ChaserWhenNear :EnemyBehaviour {
	void update() override;
};

struct Shooting :EnemyBehaviour {
	void update() override;
};