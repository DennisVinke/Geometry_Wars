#pragma once

#include <memory>
#include "opengl/ShaderState.h"
#include "opengl/Texture.h"


/// class Background
/*
 *  class that is used to draw the background of the game. Draws to the currently active framebuffer.
 */
class Background
{

public:

    /// enum class Theme.
    /*
     *  Enum class that contains all possbible themes that can be used as a background for the game.
     */
    enum class Theme : int
    {
        LIGHT_THEME,
        DARK_THEME,
        GEOMETRIC_THEME
    };


    /// constructor.
    /*
     *  constructs the necessary resources to draw the background, how the background will look 
     *  depends on the Theme passes as parameter.
     */
    Background(Theme theme);


    /// render().
    /*
     *  renders the scene depending on the current theme. Make sure to call this when the correct 
     *  framebuffer is active, this class does not have it's own framebuffer, but renders to the
     *  currently active one. 
     */
    void render();


    /// render_welcome_screen();
    /*
     *  renders the screen you see when you startup the game, this is rendered to the currently
     *  active framebuffer.
     */
    void render_welcome_screen();


    /// window_resized()
    /*
     *  When the window is resized this class needs to know the new dimensions in order to keep 
     *  the background being drawn correctly. Make sure this is always called on resizes.
     */
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
