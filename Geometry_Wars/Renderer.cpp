

#include "glm_type_registration.h"

#include "Renderer.h"
#include "ShaderManager.h"

#include "io/load_file_to_string.h"

#include "opengl/Shader.h"
#include "opengl/ShaderState.h"
#include "opengl/Attribute.h"
#include "opengl/Uniform.h"

#include <iostream>
#include <utility>
#include <queue>





Renderer::Renderer()
{
    glEnable(GL_PROGRAM_POINT_SIZE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 1);

    auto [path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "shaders";

    if (fs::exists(shaders_folder) && fs::is_directory(shaders_folder))
    {
        std::cout << "Shaders folder found at:\n";
        std::cout << shaders_folder << '\n';
    }
    else
    {
        std::cout << "Unable to locate \'shaders\' folder.";
    }

    auto shader = ShaderManager::add_shader("default");

    shader->add_shader_stage(load_file_to_string(shaders_folder / "default.vert"), GL_VERTEX_SHADER);
    shader->add_shader_stage(load_file_to_string(shaders_folder / "default.frag"), GL_FRAGMENT_SHADER);

    shader->add_attribute({ 0, "position", Type::VEC2 });
    shader->add_attribute({ 1, "color", Type::VEC4 });

    shader->add_uniform({ "transformation", Type::MAT_3x3 });
    shader->add_static_uniform({ "viewport", Type::VEC2 });


    shader->compile();


    default_state = std::make_unique<ShaderState>(*shader);


    default_state->activate();

    default_state->attribute["position"] = std::vector<glm::vec2>{ {400, 0 }, { 800, 800 }, { 0, 600 } };

    default_state->attribute["color"] = std::vector<glm::vec4>{ { 0, 1, 1, 1 }, { 1, 0, 1, 1 }, { 1, 0, 1, 1 } };

    default_state->uniform["transformation"] = glm::mat3(1);

}




Renderer::~Renderer()
{
    ShaderManager::free_all();
}


void Renderer::render_frame()
{
    default_state->activate();

    glDrawArrays(GL_TRIANGLES, 0, 3);
}




void Renderer::resized(int w, int h)
{
    glViewport(0, 0, w, h);
    ShaderManager::get("default")->static_uniform["viewport"] = glm::vec2(w, h);
}
