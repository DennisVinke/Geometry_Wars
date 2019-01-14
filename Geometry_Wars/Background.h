#pragma once

#include <memory>
#include "opengl/ShaderState.h"
#include "opengl/Texture.h"



class Background
{

public:

    enum class Theme : int
    {
        LIGHT_THEME,
        DARK_THEME,
        GEOMETRIC_THEME
    };

    Background(Theme theme);


    void render();


    void render_welcome_screen();

    void window_resized(unsigned int w, unsigned int h);


private:

    Theme theme;

    int amount = 800;
    
    std::unique_ptr<Texture> welcome_screen;
    std::unique_ptr<Texture> light_theme;
    std::unique_ptr<Texture> dark_theme;

    std::unique_ptr<ShaderState> background_shader;
    std::unique_ptr<ShaderState> centred_texture_shader;
    std::unique_ptr<ShaderState> full_texture_shader;

    std::vector<glm::vec2> coordinates;
    std::vector<float> colors;

    float width = 0;
    float height = 0;

};