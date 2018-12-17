#pragma once

#include "GaussianBlur.h"

#include "Shape.h"

#include "opengl/Shader.h"
#include "opengl/FrameBuffer.h"


class RenderComponent;



/// class Renderer: Responsible for rendering entities to the screen
/*
 *  Renderer holds a queue of components that require to be rendered.
 *  Furthermore it is the class responsible for updating all systems, shaders
 *  and entities that need to know the current size of the screen.
 */
class Renderer
{

public:

    /// Renderer, constructor
    Renderer();


    /// Renderer, Destructor
    ~Renderer();


    /// Executed once per frame by the Game class to render all components queued to render.
    void render_frame();


    /// Update necessary systems, shaders, framebuffers etc, about the resizing of the game.
    void resized(int w, int h);


    /// Used to register Components that want to be rendered this frame. 
	void queueToRender(RenderComponent *);

private:

	std::vector<RenderComponent *> renderables;
    Shape shape{ { {-10, -10}, { -10, 10 }, { 10, 10}, { 10, -10} } };


    //std::unique_ptr<ShaderState> triangle_1;
    //std::unique_ptr<ShaderState> triangle_2;
    
    std::unique_ptr<ShaderState> msaa_resolver;

    std::unique_ptr<ShaderState> render_texture;



    FrameBuffer frame_buffer_1{ 640, 480 };
    FrameBuffer frame_buffer_2{ 640, 480 };

    GaussianBlur blur_filter{ 640, 480, 0.5, 4 };


};

