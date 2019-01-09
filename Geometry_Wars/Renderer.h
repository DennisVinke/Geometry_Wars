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

    std::unique_ptr<ShaderState> msaa_resolver;
    std::unique_ptr<ShaderState> render_texture;
    std::unique_ptr<ShaderState> combine_shader;

    std::vector<Shape> test_shapes{ 30 };

    FrameBuffer frame_buffer_1{ 640, 480 };
    FrameBuffer frame_buffer_2{ 640, 480 };
    FrameBuffer combined_blur{ 640, 480 };

    GaussianBlur blur_near{ 640, 480, 0.8, 4 };
    GaussianBlur blur_far{ 640, 480, 0.60, 4 };

};

