#include "CollisionManager.h"
#include "EntityManager.h"
#include "MovementComponent.h"

CollisionManager::~CollisionManager() {}

void CollisionManager::Update() {
	
//	for (int i = 0; i < collideTree.count;i++) {
		//auto entity = collideTree
//	}

	CleanUp();
}

void CollisionManager::RegisterEntity(CollideComponent * collideComponent) {
	glm::vec2 pos = collideComponent->entity->getComponent<MovementComponent>()->getLocation();
	collideTree[((int)pos.x)%TREESLICE].insert(std::make_pair(((int)pos.y)%TREESLICE, collideComponent));
}

void CollisionManager::CleanUp(){
	collideTree.clear();
	collisions.clear();
}

void CollisionManager::ResolveCollisions() {
	for (auto colEvent : collisions) {
		colEvent.entity1->onCollision();
		colEvent.entity2->onCollision();
	}
}

void CollisionManager::RemoveDupplicateCollisions() {

}