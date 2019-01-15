#pragma once
#include "engine/Component.h"
#include "components/MovementComponent.h"
#include "graphics/Shape.h"

class EnemyBehaviour;

/// class EnemyBehaviourComponent: A component responsible for moving the AI of entities. 
/*
 *	This class is responsible for updating entities that are controlled by AI
 *	Different kind of behaviours can be used by including an EnemyBehaviour on instantiation
 *	Currently supports Chase, Random, Chase in Radius, Shoot and Chase behaviours are included.
 *	New behaviours can be made by deriving from the EnemyBehaviour class;
 */
class EnemyBehaviourComponent: public Component{
public:
	/// Constructor
	/*
	*	Initializes component with a predefined behaviour and a reference to entity controlled by the player
	*	@param EnemyBehaviour * The Behaviour the AI will conduct
	*	@param Entity *  reference to player controlled entity
	*/
	EnemyBehaviourComponent(EnemyBehaviour *, Entity *);
	~EnemyBehaviourComponent();

	void execute() override;
	void init() override;
	void print() override;
	
	/// set_player_position(MovementComponent *)
	/*
	*	Changes the reference to the players position
	*	@param EnemyBehaviour * The Behaviour the AI will conduct
	*	@param MovementComponent * reference to the movementComponetn of the player
	*/
	void set_player_position(MovementComponent *);
private:
	Entity * player;
	EnemyBehaviour * behaviour;
};