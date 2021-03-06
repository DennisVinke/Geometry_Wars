#include "components/CollideComponent.h"
#include "components/MovementComponent.h"

#include "engine/EntityManager.h"
#include "engine/CollisionManager.h"


CollideComponent::CollideComponent(CollisionManager& cm, CollideMask mask):Component(), colMan(cm), MaskId(mask){}

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
		
		auto sqDistance = 2 * abs(posSelf.x - posOther.x) + 2 * abs(posSelf.y - posOther.y);
		if (sqDistance < 2*(this->GetCollisionRadius() + other->GetCollisionRadius())) {
			return true;
		}
	}
	return false;
}

int CollideComponent::GetCollisionRadius() {
	return collisionRadius;
}

void CollideComponent::onCollision() {
	if (get_mask() != CollideMask::PLAYER) {
	entity->removeAllComponents();
}
	else {
		entity->getComponent<MovementComponent>()->setPosition(glm::vec2(400, 400));
	}

	//std::cout << "I have collided!" << std::endl;
}
void CollideComponent::SetCollisionRadius(int radius) {
	collisionRadius = radius;
}

CollideMask CollideComponent::get_mask() {
	return MaskId;
}

