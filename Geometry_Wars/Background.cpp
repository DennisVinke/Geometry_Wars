#include "Background.h"

#include "ShaderManager.h"
#include "glm_type_registration.h"

#include "math_utils.h"

#include <glm/gtc/constants.hpp>

#include "io/load_file_to_string.h"

#include <iostream>
#include <SDL.h>



Background::Background(Background::Theme theme_)
    : theme(theme_)
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto data = path / "data";

    auto sdl_welcome_img = SDL_LoadBMP((data / "welcome_screen.bmp").string().c_str());
    auto sdl_light_img = SDL_LoadBMP((data / "light_theme.bmp").string().c_str());
    auto sdl_dark_img = SDL_LoadBMP((data / "dark_theme.bmp").string().c_str());

    welcome_screen = std::make_unique<Texture>(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA);
    light_theme = std::make_unique<Texture>(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGB);
    dark_theme = std::make_unique<Texture>(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGB);

    welcome_screen->allocate_filled(sdl_welcome_img->w, sdl_welcome_img->h, (const unsigned char*) sdl_welcome_img->pixels);
    light_theme->allocate_filled(sdl_light_img->w, sdl_light_img->h, (const unsigned char*)sdl_light_img->pixels);
    dark_theme->allocate_filled(sdl_dark_img->w, sdl_dark_img->h, (const unsigned char*)sdl_dark_img->pixels);

    SDL_FreeSurface(sdl_welcome_img);
    SDL_FreeSurface(sdl_light_img);
    SDL_FreeSurface(sdl_dark_img);



    glEnable(GL_FRONT_AND_BACK);
    coordinates.reserve(2 * amount);
    colors.reserve(2 * amount);

    for (int i = 0; i < amount; ++i)
    {
        glm::vec2 position{ random(-1.4f, 1.4f), random(-1.4f, 1.4f) };
        coordinates.emplace_back(position + glm::vec2(random(0.2f, 0.4f), random(-0.3f, 0.3f)));
        coordinates.emplace_back(position + glm::vec2(random(-0.4f, -0.2f), random(-0.3f, 0.3f)));
        //coordinates.emplace_back(pos + glm::vec2(random(-0.4f, 0.4f), random(-0.2f, 0.2f)));
        colors.emplace_back(random(0.07f));
        colors.emplace_back(colors.back());
        //colors.emplace_back(colors.back());
    }

    background_shader = std::make_unique<ShaderState>(*ShaderManager::get("background"));
    background_shader->attribute["position"] = coordinates;
    background_shader->attribute["color"] = colors;

    centred_texture_shader = std::make_unique<ShaderState>(*ShaderManager::get("texture"));
    centred_texture_shader->attribute["tex_coord"] = std::vector<glm::vec2>{ {0, 1}, {1, 1}, {0, 0}, {1, 1}, {1, 0}, {0, 0} };

    full_texture_shader = std::make_unique<ShaderState>(*ShaderManager::get("texture"));
    full_texture_shader->attribute["tex_coord"] = std::vector<glm::vec2>{ {0, 1}, {1, 1}, {0, 0}, {1, 1}, {1, 0}, {0, 0} };
}



void Background::render()
{
    if (theme == Theme::GEOMETRIC_THEME)
    {
        background_shader->activate();

        glDrawArrays(GL_LINES, 0, amount);
    }
    else if (theme == Theme::LIGHT_THEME)
    {
        full_texture_shader->activate();

        glActiveTexture(GL_TEXTURE0);
        light_theme->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else if (theme == Theme::DARK_THEME)
    {
        full_texture_shader->activate();

        glActiveTexture(GL_TEXTURE0);
        dark_theme->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}


void Background::render_welcome_screen()
{
    centred_texture_shader->activate();

    glActiveTexture(GL_TEXTURE0);
    welcome_screen->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

}



void Background::window_resized(unsigned int w, unsigned int h)
{
    width = w;
    height = h;

    ShaderManager::get("texture")->static_uniform["viewport"] = glm::vec2(w, h);

    auto x_min = 0.5f * (w - (float) welcome_screen->get_width());
    auto y_min = 0.5f * (h - (float)welcome_screen->get_height());
    auto x_max = x_min + (float)welcome_screen->get_width();
    auto y_max = y_min + (float)welcome_screen->get_height();

    centred_texture_shader->attribute["position"] = std::vector<glm::vec2>{
        { x_min, y_max },
        { x_max, y_max },
        { x_min, y_min },
        { x_max, y_max },
        { x_max, y_min },
        { x_min, y_min }
    };

    full_texture_shader->attribute["position"] = std::vector<glm::vec2>{
        { 0, h },
        { w, h },
        { 0, 0 },
        { w, h },
        { w, 0 },
        { 0, 0 }
    };
}
