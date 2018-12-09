

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
        std::cout << "\nShaders folder found at:\n";
        std::cout << shaders_folder << '\n';
    }
    else
    {
        std::cout << "\nUnable to locate \'shaders\' folder.";
    }



    // ************************
    auto default_shader = ShaderManager::add_shader("default");

    default_shader->add_shader_stage(load_file_to_string(shaders_folder / "default.vert"), GL_VERTEX_SHADER);
    default_shader->add_shader_stage(load_file_to_string(shaders_folder / "default.frag"), GL_FRAGMENT_SHADER);

    default_shader->add_attribute({ 0, "position", Type::VEC2 });
    default_shader->add_attribute({ 1, "color", Type::VEC4 });

    default_shader->add_uniform({ "transformation", Type::MAT_3x3 });
    default_shader->add_static_uniform({ "viewport", Type::VEC2 });

    default_shader->compile();
    // ************************


    default_state = std::make_unique<ShaderState>(*default_shader);

    //default_state->activate();

    default_state->attribute["position"] = std::vector<glm::vec2>{ {250, 20 }, { 400, 300 }, { 30, 400 } };
    default_state->attribute["color"] = std::vector<glm::vec4>{ { 0, 1, 1, 1 }, { 1, 0, 1, 1 }, { 1, 0, 1, 1 } };
    default_state->uniform["transformation"] = glm::mat3(1);


    // ************************
    auto draw_fbo_shader = ShaderManager::add_shader("draw_fbo");

    draw_fbo_shader->add_shader_stage(load_file_to_string(shaders_folder / "draw_fbo.vert"), GL_VERTEX_SHADER);
    draw_fbo_shader->add_shader_stage(load_file_to_string(shaders_folder / "draw_fbo.frag"), GL_FRAGMENT_SHADER);

    draw_fbo_shader->add_attribute({ 0, "position", Type::VEC2 });

    draw_fbo_shader->compile();
    // ************************


    fbo_shader_state = std::make_unique<ShaderState>(*draw_fbo_shader);

    fbo_shader_state->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };

    Texture2D::Settings settings;
    settings.type = Texture2D::Type::MULTI_SAMPLED_8;
    settings.pixel_format = GL_RGBA8;
    settings.minify_filter = GL_NEAREST;
    settings.magnify_filter = GL_NEAREST;

    frame_buffer.add_texture(settings, GL_COLOR_ATTACHMENT0);
    frame_buffer.print_status();


}




Renderer::~Renderer()
{
    ShaderManager::free_all();
}


void Renderer::render_frame()
{

    glClear(GL_COLOR_BUFFER_BIT);

    frame_buffer.start_rendering();

    glClear(GL_COLOR_BUFFER_BIT);

    default_state->activate();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    frame_buffer.stop_rendering();


    fbo_shader_state->activate();
    auto& tex = frame_buffer.get_texture(0);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(tex.texture_type, tex.get_handle());

    glDrawArrays(GL_TRIANGLES, 0, 6);

}




void Renderer::resized(int w, int h)
{
    glViewport(0, 0, w, h);
    frame_buffer.resize(w, h);
    ShaderManager::get("default")->static_uniform["viewport"] = glm::vec2(w, h);
}
