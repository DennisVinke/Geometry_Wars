#pragma once

#include <glm/glm.hpp>
#include "engine/Component.h"

/*! \file RenderComponent.h
	\brief A component responsible for showing an Entity on the screen through the renderer
*/

/*! \fn RenderComponent(Renderer&)
	\brief Constructor of RenderComponent

	\param a reference to the renderer used by the game.
*/

/*! \fn ~RenderComponent()
	\brief Destructor of RenderComponent
*/

/*! \fn execute()
	\brief Override function to execute component logic every update. Makes shape object ready for rendering and makes a request to the renderer
*/

/*! \fn init()
	\brief Override function to init component when created. Used when old components are reused. If created please use the constructor
*/

/*! \fn print()
	\brief Override function to print the name of the component to the console. Only used for testing!
*/

/*! \fn render()
	\brief adds the shape to the renderer
*/

/*! \fn setColor(int r, int g, int b, int alpha)
	\brief sets the color of a shape

	\param r the red value between 0 and 255
	\param g the green value between 0 and 255
	\param b the blue value between 0 and 255
	\param a the alpha value between 0 and 255
*/

/*! \var Renderer& renderer
	\brief Contains a reference to the renderer used by the game
*/

/*! \var Shape shape
	\brief Contains the shape that should be drawn by the renderer
*/
enum class CollideMask:int {
PLAYER,
ENEMY,
BULLET,
ENEMYBULLET,
POWERUP
};

class CollisionManager;
class CollideComponent : public Component
{
public:
	CollideComponent() = delete;
	CollideComponent(CollisionManager& colManager, CollideMask id);
	CollideComponent(CollisionManager&) = delete;
	~CollideComponent();

	void execute() override;
	void init() override;
	void print() override;

	virtual bool hasCollision(glm::vec2 otherPosition, int size);
	virtual bool hasCollision(CollideComponent *);
	void onCollision();

	void SetCollisionRadius(int radius);
	int GetCollisionRadius();
	CollideMask get_mask();
private:
	CollisionManager& colMan;
	int collisionRadius;
	CollideMask MaskId;
};

