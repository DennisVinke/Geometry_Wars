#include "GameObjectSpawner.h"
#include "Components.h"

#include <SDL.h>

/*
GameObjectSpawner::GameObjectSpawner(EntityManager& em):entity_manager(em) {}
GameObjectSpawner::~GameObjectSpawner() {}

void GameObjectSpawner::SpawnObject() {

}

void GameObjectSpawner::SpawnPlayer(){
	auto entity = entity_manager.CreateEntity();
	entity->setComponent<MovementComponent>(glm::vec2(0, 0));
	blok->setComponent<InputComponent>();
	input_manager.addInputComponent(blok->getComponent<InputComponent>());
	input_manager.addKeyControl(SDL_SCANCODE_A, blok->getComponent<InputComponent>()->getActionController(0), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_D, blok->getComponent<InputComponent>()->getActionController(0), 1.0f);

	input_manager.addKeyControl(SDL_SCANCODE_W, blok->getComponent<InputComponent>()->getActionController(1), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_S, blok->getComponent<InputComponent>()->getActionController(1), 1.0f);

	//ActionController ac, cac, cacr;
	//input_manager.addKeyControl(SDL_SCANCODE_P, ac, 1.f);
	//input_manager.addMouseControl(1, cac, 1.f);
	//input_manager.addMouseControl(3, cacr, 1.f);
	blok->setComponent<RenderComponent>(renderer);

	blok->setComponent<CollideComponent>(collision_manager, CollideMask::PLAYER);
	blok->getComponent<CollideComponent>()->SetCollisionRadius(10);
}

void GameObjectSpawner::SpawnBullet(){

}

*/