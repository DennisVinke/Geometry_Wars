#pragma once

#include <map>

#include "CollideComponent.h"

constexpr auto TREESLICE = 100;

struct CollisionEvent {
	CollideComponent * entity1;
	CollideComponent * entity2;
};

class CollisionManager{
public:
	CollisionManager();
	~CollisionManager();
	void RegisterEntity(CollideComponent * entity);
	void Update();

private:
	void CleanUp();
	void ResolveCollisions();
	void RemoveDupplicateCollisions(); // is deze niet overbodig?
	
	std::vector<CollideComponent*> entities;

	//std::map<int, std::map<int, CollideComponent *>> collideTree;
	std::vector<std::vector<CollideComponent *>> sortedCollideComponents;
	std::vector<CollisionEvent> collisions;
	
};