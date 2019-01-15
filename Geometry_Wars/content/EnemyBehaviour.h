#pragma once
#include "components/MovementComponent.h"
#include "graphics/Shape.h"

/// struct EnemyBehaviour: Base class of all the enemy AI behaviours.
/*
 *  EnemyBehaviour struct is the interface for all EnemyBehaviour types.
 *  This class contains data on how an entity containing this behaviour should act and look
 *  Every derived class needs to have its own implementation for update. 
 */
struct EnemyBehaviour 
{

public:
	/// bulletBeahaviour
	/*
	*	Indicate which type of gun this behaviour should use
	*/
	int bulletBehaviour = 0;
	/// red, green, blue, alpha
	/*
	*	The initial value of red, green, blue, alpha of an entity with this behaviour 
	*/
	int red = 125;
	int green = 255;
	int blue = 255;
	int alpha = 0;

	/// speed
	/*
	*	The initial speed a bullet entity with this behaviour moves with
	*/
	glm::vec2 speed = glm::vec2(1, 1);
	
	/// size
	/*
	*	The initial collide radius an entity with this behaviour  
	*/
	int size = 10;
	
	/// cooldown
	/*
	*	The initial rate of fire of an entity 
	*/
	int cooldown;

	/// movement_speed
	/*
	*	The initial speed an entity with this behaviour moves with
	*/
	float movement_speed;

	/// shape
	/*
	*	The initial shape an entity with this behaviour starts with
	*/
	std::vector<glm::vec2> shape;

	/// player_position
	/*
	*	The current position of the player controlled entity
	*/
	glm::vec2 player_position;
	
	/// update(Entity *, glm::vec2 player_position)
	/*
	*	Determines the movement of a entity with the implemented behaviour 
	*	@param Entity * of the component containing this behaviour
	*	@param player_position play
	*	@return a 2d vector that the entity should move during his update
	*/
	virtual glm::vec2 update(Entity *, glm::vec2 player_position) = 0;
private:
	/// current_position
	/*
	*	A pointer to the movementComponent for the entity to request its own position;
	*/
	MovementComponent * current_position;
};
/// struct Chaser: AI behaviour that chases player controlled entity.
/*
 *  Chaser struct implements (is derived of) EnemyBehaviour.
 *  This class contains data on how to chasing objects should look and 
 *  how to chase the enemy controlled player.
 */
struct Chaser :EnemyBehaviour 
{
	/// Default constructor.
   /*
	*  When using this constructor the default values for entities 
	*  implementing this behaviour is initilized
	*  An empty constructed means it uses the default base class values
	*/
    Chaser()
    {
        red = 125;
        blue = 255;
        green = 255;
        alpha = 255;
        speed = glm::vec2(5, 5);
        shape = { {0, 20}, {20, 0}, {0, -20}, {-20, 0} };
		size = 10;
    }

	/// update(Entity *, glm::vec2 player_position)
	/*
	*	Determines the movement of a entity with the implemented behaviour
	*	@param Entity * of the component containing this behaviour
	*	@param player_position play
	*	@return a 2d vector that the entity should move during his update to chase the player
	*/
    glm::vec2 update(Entity *, glm::vec2 player_position) override;

};

struct Random :EnemyBehaviour 
{
	/// Default constructor.
   /*
	*  When using this constructor the default values for entities
	*  implementing this behaviour is initilized. 
	*  An empty constructed means it uses the default base class values
	*/
    Random()
    {

    }
	/// update(Entity *, glm::vec2 player_position)
	/*
	*	Determines the movement of a entity with the implemented behaviour
	*	@param Entity * of the component containing this behaviour
	*	@param player_position play
	*	@return a 2d vector that the entity should move during his update
	*/
	glm::vec2 update(Entity *, glm::vec2 player_position) override;

};
struct ChaserWhenNear :EnemyBehaviour 
{	
	/// Default constructor.
   /*
	*  When using this constructor the default values for entities
	*  implementing this behaviour is initilized.
	*  An empty constructed means it uses the default base class values
	*/
    ChaserWhenNear()
    {

    }

	/// update(Entity *, glm::vec2 player_position)
	/*
	*	Determines the movement of a entity with the implemented behaviour
	*	@param Entity * of the component containing this behaviour
	*	@param player_position play
	*	@return a 2d vector that the entity should move during his update
	*/
	glm::vec2 update(Entity *, glm::vec2 player_position) override;
	
	/// min_chase_distance
	/*
	*	The radius in which the behaviour starts to chase
	*/
	int min_chase_distance = 100;
};

struct Shooting : Chaser 
{
	/// Default constructor.
   /*
	*  When using this constructor the default values for entities
	*  implementing this behaviour is initilized.
	*  An empty constructed means it uses the default base class values
	*/
    Shooting()
    {

    }

	/// Default constructor.
   /*
	*  When using this constructor the default values for entities
	*  implementing this behaviour is initilized.
	*  An empty constructed means it uses the default base class values
	*/
	glm::vec2 update(Entity *, glm::vec2 player_position);

private:
	glm::vec2 shoot_speed =  glm::vec2(1, 1);
};