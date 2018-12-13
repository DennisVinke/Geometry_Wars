#pragma once

#include "GaussianBlur.h"

#include "Shape.h"

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


    Shape shape{ { {-10, -10}, { -10, 10 }, { 10, 10}, { 10, -10} } };


    //std::unique_ptr<ShaderState> triangle_1;
    //std::unique_ptr<ShaderState> triangle_2;
    
    std::unique_ptr<ShaderState> msaa_resolver;

    std::unique_ptr<ShaderState> render_texture;



    FrameBuffer frame_buffer_1{ 640, 480 };
    FrameBuffer frame_buffer_2{ 640, 480 };

    GaussianBlur blur_filter{ 640, 480, 0.5, 4 };


};

