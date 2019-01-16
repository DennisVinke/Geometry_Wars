#pragma once

#include <glm/glm.hpp>
#include "engine/Component.h"

/// enum class CollideMask.
/**
 *  enum to define different kind of collision objects.
 */
enum class CollideMask:int {
PLAYER,
ENEMY,
BULLET,
ENEMYBULLET,
POWERUP
};

class CollisionManager;

/// class CollideComponent: A component responsible for collisions between Entities and how to deal when a collision happens. 
/**
 *	This class is responsible for looking if it collides with a given entity 
 *  and how what to do when a collision with this entity has been done
 *	Currently only supports circle collision
 *	Every entity that wants to use collisions should contain this component 
 *	If you want to define your own collision logic, use this as baseclass
 *  and override the hasCollision and onCollision methods
 */
class CollideComponent : public Component
{
public:
	CollideComponent() = delete;

	/// Constructor
	/**
	*	Initializes component with a collisionMask and a reference to the game's CollisionManager
	*	@param CollisionManager& colManager reference to CollisionManager
	*	@param CollideMasl id identifier of kind of collision object this component is.
	*/
	CollideComponent(CollisionManager& colManager, CollideMask id);
	CollideComponent(CollisionManager&) = delete;
	~CollideComponent();

	void execute() override;
	void init() override;
	void print() override;
	
	/// hasCollision(glm::vec2 otherPosition, int size)
	/// hasCollision(CollideComponent *)
	/**
	*	Checks if the current component has a collision with the other component
	*	Can be overriden if other collisionCheckingMethod has to be implemented
	*	@param CollideComponent * information about the other component
	*	@return if there is a collision with the other component
	*/
	virtual bool hasCollision(glm::vec2 otherPosition, int size);
	virtual bool hasCollision(CollideComponent *);
	
	/// hasCollision()
	/**
	*	executes what needs to be done on collision
	*	Can be overriden if other onCollisionBehaviour has to be implemented
	*/
	virtual void onCollision();

	/// setCollisionRadius(int radius)
	/**
	*	Sets the radius used for collision check
	*	@param int radius new radius value
	*/
	void SetCollisionRadius(int radius);

	/// getCollisionRadius()
	/**
	*	gets the radius used for collision check
	*	@return circle radius used for collision check
	*/
	int GetCollisionRadius();
	
	/// get_mask()
	/**
	*	get the type of collision type the component is
	*	@return type of collision object this component is
	*/
	CollideMask get_mask();

private:
	CollisionManager& colMan;
	int collisionRadius;
	CollideMask MaskId;
};

