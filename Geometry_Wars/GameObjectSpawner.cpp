#include "GameObjectSpawner.h"
#include "Components.h"
#include "ShootComponent.h"
#include "Game.h"


GameObjectSpawner::GameObjectSpawner(Game& gme):game(gme),entity_manager(gme.get_entity_manager()), input_manager(gme.get_input_manager()), collision_manager(gme.get_collision_manager()), renderer(gme.get_renderer()) {}
GameObjectSpawner::~GameObjectSpawner() {}


void GameObjectSpawner::spawn_object() {

}

void GameObjectSpawner::spawn_player(){
	auto entity = game.get_entity_manager().CreateEntity();
	entity->setComponent<MovementComponent>(glm::vec2(0, 0));
	entity->setComponent<InputComponent>();
	game.get_input_manager().addInputComponent(entity->getComponent<InputComponent>());
	input_manager.addKeyControl(SDL_SCANCODE_A, entity->getComponent<InputComponent>()->getActionController(0), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_D, entity->getComponent<InputComponent>()->getActionController(0), 1.0f);

	input_manager.addKeyControl(SDL_SCANCODE_W, entity->getComponent<InputComponent>()->getActionController(1), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_S, entity->getComponent<InputComponent>()->getActionController(1), 1.0f);
	
	input_manager.addMouseControl(1, entity->getComponent<InputComponent>()->getActionController(2), 1.0f);

	input_manager.addMouseControl(SDL_SCANCODE_R, entity->getComponent<InputComponent>()->getActionController(4), 1.0f);


	//ActionController ac, cac, cacr;
	//input_manager.addKeyControl(SDL_SCANCODE_P, ac, 1.f);
	//input_manager.addMouseControl(1, cac, 1.f);
	//input_manager.addMouseControl(3, cacr, 1.f);
	entity->setComponent<RenderComponent>(renderer);

	entity->setComponent<CollideComponent>(collision_manager, CollideMask::PLAYER);
	entity->getComponent<CollideComponent>()->SetCollisionRadius(10);
	entity->setComponent<ShootComponent>(*this);

}

void GameObjectSpawner::spawn_bullet(Weapon * bullet_info, glm::vec2 spawn_position) {
	auto entity = game.get_entity_manager().CreateEntity();
	entity->setComponent<MovementComponent>(spawn_position);

/*
	spawn.x *= 5;
	spawn.y *= 5;
	gameObjects.back()
	*/
	entity->getComponent<MovementComponent>()->setConstantMovement(glm::vec2(1,0));
	entity->setComponent<RenderComponent>(renderer);
	
	/*
	gameObjects.back()->setComponent<CollideComponent>(collisionManager, CollideMask::BULLET);
	gameObjects.back()->getComponent<CollideComponent>()->SetCollisionRadius(10);
	*/

	auto render_component = entity->getComponent<RenderComponent>();
	render_component->shape.set_line_width(7);
	render_component->shape.set_draw_mode(GL_POINTS);
	render_component->shape.set_shape({ {0, 0} });
	
	entity->getComponent<RenderComponent>()->setColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
	
}

