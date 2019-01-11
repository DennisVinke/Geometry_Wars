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

bool CollideComponent::hasCollision(CollideComponent* other) {
	if (entity->hasComponent<MovementComponent>() && other->entity->hasComponent<MovementComponent>()) {
		auto posSelf = entity->getComponent<MovementComponent>()->getLocation();
		auto posOther = other->entity->getComponent<MovementComponent>()->getLocation();
		
		auto sqDistance = 2 * (posSelf.x - posOther.x) + 2 * (posSelf.y - posOther.y);
		if (sqDistance < (this->GetCollisionRadius() + other->GetCollisionRadius())) {
			return true;
		}
	}
	return false;
}

int CollideComponent::GetCollisionRadius() {
	return collisionRadius;
}

void CollideComponent::onCollision() {
	entity->removeComponent<CollideComponent>();

	//std::cout << "I have collided!" << std::endl;
}
void CollideComponent::SetCollisionRadius(int radius) {
	collisionRadius = radius;
}

