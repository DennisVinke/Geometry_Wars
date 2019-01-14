#pragma once

#include <glm/glm.hpp>
#include "Component.h"
#include "Weapon.h"

class GameObjectSpawner;


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