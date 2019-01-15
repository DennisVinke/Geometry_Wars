#include "components/EnemyBehaviourComponent.h"
#include "content/EnemyBehaviour.h"
#include "engine/EntityManager.h"

EnemyBehaviourComponent::EnemyBehaviourComponent(EnemyBehaviour*bhvir, Entity* plyer):Component(), behaviour(bhvir), player(plyer)
{
}

EnemyBehaviourComponent::~EnemyBehaviourComponent() {}

void EnemyBehaviourComponent::execute() {
	glm::vec2 movement = behaviour->update(entity, player->getComponent<MovementComponent>()->getLocation());
	entity->getComponent<MovementComponent>()->doMovement(movement);
}

void EnemyBehaviourComponent::init() {}

void EnemyBehaviourComponent::print() {}

void EnemyBehaviourComponent::set_player_position(MovementComponent *) {}

