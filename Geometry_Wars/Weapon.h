#pragma once
#include <glm/glm.hpp>
class GameObjectSpawner;

class Weapon {
public:
	int bulletBehaviour = 0;
	int red, green, blue, alpha = 0;
	glm::vec2 speed = glm::vec2(0, 0);
	int size = 1;
	int cooldown;
	virtual void gunBehaviour(GameObjectSpawner& spawner, glm::vec2 spawn_position, glm::vec2 click_position) = 0;
};

class SingleShotGun : public Weapon {
public:
	inline SingleShotGun() {
		red = 100;
		blue = 100;
		green = 100;
		alpha = 190;
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