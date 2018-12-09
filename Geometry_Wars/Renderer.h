#pragma once

#include "opengl/Shader.h"
#include "opengl/FrameBuffer.h"



class Renderer
{

public:

    Renderer();

    ~Renderer();

    void render_frame();


    void resized(int w, int h);


private:

    std::unique_ptr<ShaderState> default_state;
    
    std::unique_ptr<ShaderState> fbo_shader_state;


    FrameBuffer frame_buffer{ 640, 480 };

};
