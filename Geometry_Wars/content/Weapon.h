#pragma once
#include <glm/glm.hpp>
class GameObjectSpawner;

class Weapon {
public:
	int bulletBehaviour = 0;
	int red, green, blue, alpha = 0;
	glm::vec2 speed = glm::vec2(1, 1);
	int size = 10;
	float cooldown=.25;
	int mask = 2;
	glm::vec2 direction;
	virtual void gunBehaviour(GameObjectSpawner& spawner, glm::vec2 spawn_position, glm::vec2 click_position) = 0;
	inline void set_mask(int new_mask) {
		mask = new_mask;
	}
};

class SingleShotGun : public Weapon {
public:
	inline SingleShotGun() {
		red = 0;
		blue = 255;
		green = 255;
		alpha = 255;
		speed = glm::vec2(3,3);
	}
	void gunBehaviour(GameObjectSpawner & spawn, glm::vec2 spawn_position, glm::vec2 click_position) override;
};

class DoubleShotGun : public Weapon {
public:
	inline DoubleShotGun() {
		red = 200;
		blue = 200;
		green = 200;
		alpha = 170;
	}
	void gunBehaviour(GameObjectSpawner & spawn, glm::vec2 spawn_position, glm::vec2 click_position) override;
};

class TripleShotGun : public Weapon {
public:
	inline TripleShotGun() {
		red = 50;
		blue = 20;
		green = 190;
		alpha = 255;
	}
	void gunBehaviour(GameObjectSpawner & spawn, glm::vec2 spawn_position, glm::vec2 click_position) override;
};

class EnemyGun : public SingleShotGun {
public: 
	inline	EnemyGun() {
		red = 255;
		blue = 10;
		green = 25;
		alpha = 255;
		glm::vec2(3, 3);
		mask = 3;
	}
};