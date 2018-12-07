#pragma once

#include "Shader.h"




class Renderer
{

public:

    Renderer();

    ~Renderer();

    void render_frame();


    void resized(int w, int h);


private:

    std::unique_ptr<ShaderState> default_state;


};
