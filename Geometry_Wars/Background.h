#pragma once

#include <memory>
#include "opengl/ShaderState.h"
#include "opengl/Texture.h"



class Background
{

public:

    Background();


    void render();


    void render_welcome_screen();

    void window_resized(unsigned int w, unsigned int h);


private:

    int amount = 800;
    
    std::unique_ptr<Texture> welcome_screen;

    std::unique_ptr<ShaderState> background_shader;
    std::unique_ptr<ShaderState> texture_shader;

    std::vector<glm::vec2> coordinates;
    std::vector<float> colors;

    float width = 0;
    float height = 0;

};