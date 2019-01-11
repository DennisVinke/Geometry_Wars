#include "Background.h"

#include "ShaderManager.h"
#include "glm_type_registration.h"

#include "random.h"

#include <glm/gtc/constants.hpp>

#include <io/load_file_to_string.h>


#include <SDL.h>



Background::Background()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto file = path / "data" / "welcome_screen.bmp";

    auto img = SDL_LoadBMP(file.string().c_str());
   
    // upload to gpu here

    welcome_screen = std::make_unique<Texture>(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA);
    welcome_screen->allocate_filled(img->w, img->h, (const unsigned char*) img->pixels);

    SDL_FreeSurface(img);

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

    texture_shader = std::make_unique<ShaderState>(*ShaderManager::get("texture"));
    texture_shader->attribute["tex_coord"] = std::vector<glm::vec2>{ {0, 1}, {1, 1}, {0, 0}, {1, 1}, {1, 0}, {0, 0} };
}



void Background::render()
{
    background_shader->activate();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawArrays(GL_LINES, 0, amount);




    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void Background::render_welcome_screen()
{
    texture_shader->activate();

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

    texture_shader->attribute["position"] = std::vector<glm::vec2>{
        { x_min, y_max },
        { x_max, y_max },
        { x_min, y_min },
        { x_max, y_max },
        { x_max, y_min },
        { x_min, y_min }
    };
}
