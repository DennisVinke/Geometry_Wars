#include "GameObjectSpawner.h"
#include "Components.h"
#include "ShootComponent.h"
#include "Game.h"
#include "Weapon.h"
#include "EnemyBehaviour.h"

GameObjectSpawner::GameObjectSpawner(Game& gme):game(gme),entity_manager(gme.get_entity_manager()), input_manager(gme.get_input_manager()), collision_manager(gme.get_collision_manager()), renderer(gme.get_renderer()) {}
GameObjectSpawner::~GameObjectSpawner() {}


void GameObjectSpawner::spawn_object() {

}

void GameObjectSpawner::spawn_player(){
	//create Components
	auto entity = game.get_entity_manager().CreateEntity();
	entity->setComponent<MovementComponent>(glm::vec2(0, 0));
	entity->setComponent<InputComponent>();

	//Adding controls to the 
	game.get_input_manager().addInputComponent(entity->getComponent<InputComponent>());
	input_manager.addKeyControl(SDL_SCANCODE_A, entity->getComponent<InputComponent>()->getActionController(0), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_D, entity->getComponent<InputComponent>()->getActionController(0), 1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_W, entity->getComponent<InputComponent>()->getActionController(1), -1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_S, entity->getComponent<InputComponent>()->getActionController(1), 1.0f);
	input_manager.addMouseControl(1, entity->getComponent<InputComponent>()->getActionController(2), 1.0f);
	input_manager.addKeyControl(SDL_SCANCODE_R, entity->getComponent<InputComponent>()->getActionController(4), 1.0f);


	entity->setComponent<RenderComponent>(renderer);
	entity->setComponent<CollideComponent>(collision_manager, CollideMask::PLAYER);
	entity->getComponent<CollideComponent>()->SetCollisionRadius(10);
	entity->setComponent<ShootComponent>(*this);

	player = entity;

}

void GameObjectSpawner::spawn_bullet(Weapon * bullet_info, glm::vec2 spawn_position) {
	auto entity = game.get_entity_manager().CreateEntity();
	entity->setComponent<MovementComponent>(spawn_position);

	entity->getComponent<MovementComponent>()->setConstantMovement(bullet_info->direction*bullet_info->speed);
	entity->setComponent<RenderComponent>(renderer);
	
	
	entity->setComponent<CollideComponent>(collision_manager, CollideMask(bullet_info->mask));
	entity->getComponent<CollideComponent>()->SetCollisionRadius(bullet_info->size);
	CollideMask test =entity->getComponent<CollideComponent>()->get_mask();

	auto render_component = entity->getComponent<RenderComponent>();
	render_component->shape.set_line_width(7);
	render_component->shape.set_draw_mode(GL_POINTS);
	render_component->shape.set_shape({ {0, 0} });
	
	entity->getComponent<RenderComponent>()->setColor(bullet_info->red, bullet_info->green, bullet_info->blue, bullet_info->alpha);
	SoundManager::play(Sounds::LASER);
}

void GameObjectSpawner::spawn_enemy(EnemyBehaviour* enemy_info, glm::vec2 spawn_position) {
	auto entity = game.get_entity_manager().CreateEntity();
	entity->setComponent<MovementComponent>(spawn_position);

	entity->setComponent<RenderComponent>(renderer);
	auto render_component = entity->getComponent<RenderComponent>();

	render_component->shape.set_line_width(1);
	//render_component->shape.set_draw_mode(GL_POINTS);
	//render_component->shape.set_shape({ {0, 0} });
	entity->getComponent<RenderComponent>()->setColor(enemy_info->red, enemy_info->green, enemy_info->blue, enemy_info->alpha);
	entity->setComponent<CollideComponent>(collision_manager, CollideMask::ENEMY);
	entity->getComponent<CollideComponent>()->SetCollisionRadius(enemy_info->size);
	entity->setComponent<EnemyBehaviourComponent>(enemy_info, player);

}

void GameObjectSpawner::spawn_shooting_enemy(EnemyBehaviour* enemy_info, glm::vec2 spawn_position) {
	auto entity = game.get_entity_manager().CreateEntity();
	entity->setComponent<MovementComponent>(spawn_position);

	entity->setComponent<RenderComponent>(renderer);
	auto render_component = entity->getComponent<RenderComponent>();

	render_component->shape.set_line_width(1);
	//render_component->shape.set_draw_mode(GL_POINTS);
	//render_component->shape.set_shape({ {0, 0} });
	entity->getComponent<RenderComponent>()->setColor(enemy_info->red, enemy_info->green, enemy_info->blue, enemy_info->alpha);
	entity->setComponent<CollideComponent>(collision_manager, CollideMask::ENEMY);
	entity->getComponent<CollideComponent>()->SetCollisionRadius(enemy_info->size);
	entity->setComponent<EnemyBehaviourComponent>(enemy_info, player);

	entity->setComponent<ShootComponent>(*this);
	entity->getComponent<ShootComponent>()->setWeapon(new EnemyGun());


}