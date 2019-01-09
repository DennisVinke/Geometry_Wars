#pragma once

#include <map>

#include "CollideComponent.h"


class CollisionManager{

public:
	CollisionManager();
	~CollisionManager();
	void RegisterEntity(CollideComponent * entity);

private:
	void Clean();
	std::map<int, std::map<int, CollideComponent *>> collideTree;

};