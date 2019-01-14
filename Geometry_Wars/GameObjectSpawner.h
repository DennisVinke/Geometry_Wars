#pragma once

#include "ShootComponent.h"


class Game;
class EntityManager;
class InputManager;
class CollisionManager;
class Renderer;
class Weapon;
struct EnemyBehaviour;
class GameObjectSpawner{

public:
	GameObjectSpawner() = delete;
	GameObjectSpawner(Game& gme);
	
	~GameObjectSpawner();

	void spawn_object();
	void spawn_player();
	void spawn_bullet(Weapon *, glm::vec2 spawn_position);
	void spawn_enemy(EnemyBehaviour *, glm::vec2);
	void spawn_shooting_enemy();
	void spawn_shield_enemy();
	//void set_game(Game * gme);
private:
	Game& game;
	EntityManager& entity_manager;
	InputManager& input_manager;
	CollisionManager& collision_manager;
	Renderer& renderer;

	Entity * player;
};
