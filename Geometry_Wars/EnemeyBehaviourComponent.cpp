#include "EnemyBehaviourComponent.h"
#include "EnemyBehaviour.h"

EnemyBehaviourComponent::EnemyBehaviourComponent(EnemyBehaviour*bhvir):Component(), behaviour(bhvir){}

EnemyBehaviourComponent::~EnemyBehaviourComponent() {}

void EnemyBehaviourComponent::execute() {
	behaviour->update();
}

void EnemyBehaviourComponent::init() {}

void EnemyBehaviourComponent::print() {}

void EnemyBehaviourComponent::set_player_position(MovementComponent *) {}


