#pragma once

#include <array>

#include "Shader.h"


class Renderable;

typedef int ShaderID;



class Renderer
{

public:

    enum ShaderIDs : ShaderID
    {
        DEFAULT_SHADER = 0,
        POINT_SHADER = 1,
        TOTAL_AMOUNT = 2
    };


    Renderer();


    void render(Renderable& renderable);

    
    std::array<Shader, ShaderIDs::TOTAL_AMOUNT> shaders;
    

};
