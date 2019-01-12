#pragma once
#include "EntityManager.h"


class GameObjectSpawner{
public:
	GameObjectSpawner(EntityManager& em);
	~GameObjectSpawner();

	void SpawnObject();
	void SpawnPlayer(Entity*);
	void SpawnBullet();
private:
	EntityManager& entity_manager;
};
