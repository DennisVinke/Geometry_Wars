#pragma once

#include <algorithm> 
#include <vector>
#include <utility>

#include "Entity.h"

using EntityID = std::size_t;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	EntityID getComponentID();
	//void AddEntity(IEntity&);
	Entity& CreateEntity();
	void update();
	void draw();
	void clean();
	//void 
	//virtual const int GetStaticEntityID() const = 0;

private:
	std::vector<Entity *> entities;
	EntityID lastID;
};