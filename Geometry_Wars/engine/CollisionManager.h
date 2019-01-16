#pragma once

#include <map>
#include <vector>
#include <algorithm>

#include "components/CollideComponent.h"


constexpr auto TREESLICE = 100;

//	0		1	 2		3			4
//PLAYER,ENEMY,BULLET,ENEMYBULLET,POWERUP
const std::vector<std::vector<int>> collisionTable = { {1,3},{0,2},{1},{0},{0} };


struct CollisionEvent {
	CollideComponent * entity1;
	CollideComponent * entity2;
};
/// class CollisionManager
/**
*	The CollisionManager manages all the CollidableComponents
*	Registers all the collisions in a frame and 
*	Calls the objects that collided to resolve their collision
*/
class CollisionManager{
public:
	CollisionManager();
	~CollisionManager();
	void RegisterEntity(CollideComponent * entity);
	void update();
	bool can_collide(CollideMask c1, CollideMask c2);

private:
	
	void CleanUp();
	void ResolveCollisions();
	void RemoveDupplicateCollisions(); 

	std::vector<CollideComponent*> entities;

	std::vector<std::vector<CollideComponent *>> sortedCollideComponents;
	std::vector<CollisionEvent> collisions;
	
};