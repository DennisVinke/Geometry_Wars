#include "EntityManager.h"


EntityManager::EntityManager()
{
	lastID = -1;
}


EntityManager::~EntityManager()
{
}

/**
* \returns current available ID
*/
EntityID EntityManager::getComponentID() {
	return lastID++;
}
/*
void EntityManager::AddEntity(IEntity& entity) {
	//entities.emplace_back(new );
}*/

Entity& EntityManager::CreateEntity() {
	Entity * entity = new Entity();
	//std::unique_ptr<Entity> upointEntety(entity);
	//entities.emplace_back(std::move(upointEntety));
	return * entity;
}

void::EntityManager::update() {
	for (auto entity : entities) {
		entity->update();
	}
}

void EntityManager::clean() {
}
void EntityManager::draw() {}
