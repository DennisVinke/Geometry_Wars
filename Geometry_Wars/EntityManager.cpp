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
	Entity * entity = new Entity(1);
	std::unique_ptr<Entity> upointEntety(entity);
	entities.emplace_back(std::move(upointEntety));
	return * entity;
}

/**
*
* Extra lijst bijhouden van entities die een speciale component hebben?
*
*/
void::EntityManager::update() {
	for (auto& entity : entities) {
		entity->update();
	}
	clean();

}

void EntityManager::clean() {
	for (int i = 0; i < entities.size() && !entities.empty();) {
		if (entities.at(i)->isActive()) {
			entities.at(i)->cleanUp();
			i++;
		}
		else{
			entities.at(i).swap(entities.at(entities.size() - 1));
			entities.pop_back();
		}
	}		
}

void EntityManager::draw() {}
