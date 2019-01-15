#include <algorithm> 
#include <vector>
#include <utility>

#include "engine/Component.h"
#include "engine/GameObject.h"

using ComponentID = std::size_t;

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	ComponentID getComponentID();
	//void AddEntity(IEntity&);
	Component& createComponent(Entity * entity);

	Component* createHealthComponent(GameObject * entity);

	//void 
	//virtual const int GetStaticEntityID() const = 0;

private:
	std::vector<Component *> components;
	ComponentID lastID;
};