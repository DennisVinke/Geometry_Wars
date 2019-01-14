#pragma once
#include "Game.h"
class GameObjectSpawner{
public:
	GameObjectSpawner(Game& game);
	~GameObjectSpawner();

	void SpawnObject();
	void SpawnPlayer();
	void SpawnBullet();
private:
	Game& game;
	EntityManager& entity_manager;
	InputManager& input_manager;
	CollisionManager& collision_manager;
	Renderer& renderer;

};
