#pragma once

#include <algorithm> 
#include <vector>
#include <utility>

#include "engine/Entity.h"


/// type alias that ensures Entity ID's are always a type of std::size_t
using EntityID = std::size_t;


/// type alias that ensures Component ID's are always a type of std::size_t
using ComponentID = std::size_t;



static EntityID lastEntityID = 0;

static ComponentID lastComponentID = 0;




/// Class which is responsible for the enteties  used by the game. Makes sure entities are updated, up to date and relefant.
class EntityManager
{
public:

    ///  Constructor of EntityManager
	EntityManager();

    /// Destructor of EntityManager
	~EntityManager();

    /// Reuses an unused entity if possible. Else creates a new entity and keeps a unique_ptr reference to the newly created entity
    /// \param Entity * to available "new" entity
	EntityID getComponentID();

    /// 
	Entity* CreateEntity();

    /// Updates all the active entities in the game
	void update();

    /// Look if all the current entities are still active and call the clean function for all active entities.
	void clean();


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