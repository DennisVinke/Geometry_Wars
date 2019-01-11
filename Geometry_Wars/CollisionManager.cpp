#include "CollisionManager.h"
#include "EntityManager.h"
#include "MovementComponent.h"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::Update() {
	
	//Doe het gewoon in vector<vector<CollisionComponent>>
//	for (int i = 0; i < collideTree.count;i++) {
		//auto entity = collideTree
//	}

	//look up down left right
	//for(int i=0; i< )

	
	for (int i = 0; i < entities.size();i++) {
		for (int j = i+1; j < entities.size()-1;j++) {
			if (entities.at(i)->hasCollision(entities.at(j))) {
				collisions.emplace_back(CollisionEvent{ entities.at(i) ,entities.at(j) });
				}
			}
		}
		//auto entity = collideTree
	ResolveCollisions();
	CleanUp();
}

void CollisionManager::RegisterEntity(CollideComponent * collideComponent) {
	//glm::vec2 pos = collideComponent->entity->getComponent<MovementComponent>()->getLocation();
	//collideTree[((int)pos.x)%TREESLICE].insert(std::make_pair(((int)pos.y)%TREESLICE, collideComponent));
	entities.emplace_back(collideComponent);
}

void CollisionManager::CleanUp(){
	//collideTree.clear();
	entities.clear();
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