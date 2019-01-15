#pragma once

#include <algorithm> 
#include <vector>
#include <utility>

#include "engine/Entity.h"


/*! \file EntityManager.h
	\brief Class which is responsible for the enteties  used by the game. Makes sure entities are updated, up to date and relefant.
*/

/*! \def ComponentID
	\brief type alias that ensures Component ID's are always a type of std::size_t
*/


/*! \fn EntityManager()
	\brief Constructor of EntityManager
*/

/*! \fn ~EntityManager()
	\brief Destructor of EntityManager
*/

/*! \fn CreateEntity()
	\brief Reuses an unused entity if possible. Else creates a new entity and keeps a unique_ptr reference to the newly created entity
	
	\param Entity * to available "new" entity
*/

/*! \fn update()
	\brief Updates all the active entities in the game
*/

/*! \fn draw()
	\brief Let all entities draw to the renderer. Not used anymore?
*/

/*! \fn clean()
	\brief Look if all the current entities are still active and call the clean function for all active entities.
*/

/*! \fn setCurrentHealth(int newHealth)
	\brief sets the health of an entity to the given value

	\param newHealth, the value the currentHealth should be
*/

/*! \fn setMaxHealth(int maxHealth)
	\brief sets the maximum health value an entity can have to a new value

	\param maxHealth new value for maxHealth
*/

/*! \fn updateHealth(int damage)
	\brief reduce the current health with given damage

	\param damage the value currentHealth should be changed with. Can be negative for a heal
*/

/*! \var EntityID lastID;
	\brief Contains the last number used 
*/

/*! \var std::vector<std::unique_ptr<Entity>> entities;
	\brief Contains a list with all active entities in the game
*/

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
	Entity* CreateEntity();
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