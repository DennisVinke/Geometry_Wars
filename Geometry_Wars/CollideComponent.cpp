#include "CollideComponent.h"
#include "MovementComponent.h"
#include "TransformationComponent.h"
#include "EntityManager.h"
#include "CollisionManager.h"

CollideComponent::CollideComponent(CollisionManager& cm):Component(), colMan(cm){}

void CollideComponent::execute() {
	colMan.RegisterEntity(this);
}
void CollideComponent::init() {}
void CollideComponent::print() {}

bool CollideComponent::hasCollision(glm::vec2 otherPosition, int size) {
	if (entity->hasComponent<MovementComponent>()) {
	}
	return false;
}

void CollideComponent::onCollision() {}
