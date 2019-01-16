#pragma once
#include "engine/Component.h"
#include "graphics/Renderer.h"
#include "graphics/Shape.h"


/*! \file RenderComponent.h
	\brief A component responsible for showing an Entity on the screen through the renderer
*/



class RenderComponent : public Component
{

private:


    Renderer& renderer;


public:

    /// Contains the shape that should be drawn by the renderer
    /**
     *  Contains the shape that should be drawn by the renderer
     */
    Shape shape;


    RenderComponent()=delete;


    ///  RenderComponent(Renderer&)
    /**
     *  Constructor of RenderComponent
     *  \param a reference to the renderer used by the game.
     */
	RenderComponent(Renderer&);



    ///  ~RenderComponent()
    /**
     *   Destructor of RenderComponent
     */
	~RenderComponent();


    ///  Override function to execute component logic every update. Makes shape object ready for rendering and makes a request to the renderer
    /**
     *  Override function to execute component logic every update. Makes shape object ready for rendering and makes a request to the renderer
     */
	void execute() override;


    /// Override function to init component when created. Used when old components are reused. If created please use the constructor
	void init() override;


    /// Override function to print the name of the component to the console. Only used for testing!
	void print() override;


    /// adds the shape to the renderer
	void render();


    /// returns the location of the component
	glm::vec2 getLocation();


    /// sets the color of a shape
    /**
     *      \param r the red value between 0 and 255
     *      \param g the green value between 0 and 255
     *      \param b the blue value between 0 and 255
     *      \param a the alpha value between 0 and 255
     */
	void setColor(int,int,int, int);
};

