#include "Entity.h"
#include "HealthComponent.h"		

Entity::Entity()
{
}

Entity::Entity(std::size_t _id)
{
	id = _id;
	changedComponentFlag = false;
}

Entity::~Entity()
{

}

void addComponent(Component * component) {
	if (dynamic_cast<HealthComponent *>(component) != nullptr){
		;
}
}

void removeComponent(Component * component) {
	//if()
}

/*Ga hier ff uitzoeken hoe templates nu precies werken
*/

/*
// template gedoe
void Entity::addComponent<T>(Component * component {
 
	// static assert check: std::is_base_of<>

	ComponentArray<staticCast<T> component, 1>;
}

void Entity::removeComponent() {
	//check if type
	//check if excists
	//set flag to false;
	//remove component
}*/