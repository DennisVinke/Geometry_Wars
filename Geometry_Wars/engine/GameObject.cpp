#include "engine/GameObject.h"
#include "engine/Component.h"



GameObject::GameObject(Entity& enti):entity(enti) {
}

GameObject::~GameObject()
{
}

void GameObject::update() {
	for (auto& component : componentList) {
		component.execute();
	}
}

Entity& GameObject::getEntity() {
	return entity;
}