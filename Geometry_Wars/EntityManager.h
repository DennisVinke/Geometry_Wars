#pragma once

#include <algorithm> 
#include <vector>
#include <utility>

#include "Entity.h"

using EntityID = std::size_t;
using ComponentID = std::size_t;


static EntityID lastEntityID = 0;
static ComponentID lastComponentID = 0;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	EntityID getComponentID();
	//void AddEntity(IEntity&);
	Entity& CreateEntity();
	void update();
	void draw(); //can be deleted
	void clean();
	//void 
	//virtual const int GetStaticEntityID() const = 0;
	

	//Deze een keer mooier wegwerken en dan voornamelijk in een andere header of class
	static inline ComponentID getLastComponentID() noexcept {
		return lastComponentID++;
	}
	template<typename T> static inline ComponentID getLastComponentID() noexcept {
		static ComponentID componentTypeID = getLastComponentID();
			return componentTypeID;
	}

	static inline EntityID getLastEntityID() {
		return lastEntityID++;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	EntityID lastID;
};