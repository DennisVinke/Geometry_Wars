#pragma once

#include <glm/glm.hpp>

#include "Component.h"
class GameObjectSpawner;
struct Weapon {
	int bulletBehaviour = 0;
	int red, green, blue, alpha = 0; 
	glm::vec2 speed = glm::vec2(0,0);
	int size = 1;
	int cooldown;
	virtual void gunBehaviour(GameObjectSpawner& spawner, glm::vec2 spawn_position, glm::vec2 click_position) = 0;
};

struct SingleShotGun: public Weapon {
	inline SingleShotGun() {
		red = 100;
		blue = 100;
		green = 100;
		alpha = 190;
	}
	inline void gunBehaviour(GameObjectSpawner& spawn, glm::vec2 spawn_position, glm::vec2 click_position) {
		speed = glm::vec2((click_position - spawn_position) / glm::distance(click_position, spawn_position));
		spawn.spawn_bullet(this, spawn_position);
	}
};

struct DoubleShotGun : public Weapon {
	inline DoubleShotGun() {
		red = 200;
		blue = 200;
		green = 200;
		alpha = 170;
	}
	inline void gunBehaviour(GameObjectSpawner& spawn, glm::vec2 spawn_position, glm::vec2 click_position) {
		speed = glm::vec2((click_position - spawn_position) / glm::distance(click_position, spawn_position));
	}
};

struct TripleShotGun : public Weapon {
	inline TripleShotGun() {
		red = 50;
		blue = 20;
		green = 190;
		alpha = 255;
	}
	inline void gunBehaviour(GameObjectSpawner& spawn, glm::vec2 spawn_position, glm::vec2 click_position) {
		speed = glm::vec2((click_position - spawn_position) / glm::distance(click_position, spawn_position));
	}
};

class ShootComponent : public Component {
public:
	ShootComponent(GameObjectSpawner& bullet_spwner);
	~ShootComponent();

	void execute() override;
	void init() override;
	void print() override;
	void shoot(glm::vec2 clickedPosition);
	void setBulletColor(int r, int g, int b, int a);
	void setWeapon(Weapon * weapon);
	void next_weapon();
private:
	GameObjectSpawner& bullet_spawner;
	int current_gun = 0;
	SingleShotGun  basic;
	//DoubleShotGun  double_shot;
	//TripleShotGun triple_shot;
	std::array<Weapon*, 3> weapons{new SingleShotGun(), new DoubleShotGun(), new TripleShotGun()};
	int lastFired;
};