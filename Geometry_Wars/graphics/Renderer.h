#pragma once

#include "Game.h"

#include "graphics/GaussianBlur.h"
#include "graphics/Shape.h"

#include "opengl/Shader.h"
#include "opengl/FrameBuffer.h"


class RenderComponent;
class Background;


/// class Renderer: Responsible for rendering entities to the screen
/**
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


    /// Applies the RGB distortion shader, see report for more info.
    void shake(float amount, float decrease);


    /// Executed once per frame by the Game class to render all components queued to render.
    void render_frame(Game::State game_state);


    /// Update necessary systems, shaders, framebuffers etc, about the resizing of the game.
    void resized(int w, int h);


    /// Used to register Components that want to be rendered this frame. 
	void queueToRender(RenderComponent *);


private:
	
    
    Shape a;
	
    std::vector<RenderComponent *> renderables;

    std::unique_ptr<ShaderState> msaa_resolver;
    std::unique_ptr<ShaderState> render_texture;
    std::unique_ptr<ShaderState> combine_shader;
    std::unique_ptr<ShaderState> final_shader;

    std::vector<Shape> test_shapes{ 40 };

    FrameBuffer frame_buffer_1{ 640, 480 };
    FrameBuffer frame_buffer_2{ 640, 480 };
    FrameBuffer frame_buffer_3{ 640, 480 };

    glm::mat3 r_transform{ 1 }, g_transform{ 1 }, b_transform{ 1 };

    int width, height;
    float shake_amount;
    float shake_decrease;

    GaussianBlur blur_near{ 640, 480, 0.9, 4 };

    std::unique_ptr<Background> background;

};

