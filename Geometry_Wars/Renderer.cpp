

#include "glm_type_registration.h"

#include "Shape.h"
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




    /*
    triangle_1 = std::make_unique<ShaderState>(*ShaderManager::get("default"));

    triangle_1->attribute["position"] = std::vector<glm::vec2>{ {250, 20 }, { 400, 300 }, { 30, 400 } };
    triangle_1->attribute["color"] = std::vector<glm::vec4>{ { 0, 1, 1, 1 }, { 1, 0, 1, 1 }, { 1, 0, 1, 1 } };
    triangle_1->uniform["transformation"] = glm::mat3(1);

    triangle_2 = std::make_unique<ShaderState>(*ShaderManager::get("default"));

    triangle_2->attribute["position"] = std::vector<glm::vec2>{ {150, 120 }, { 700, 200 }, { 400, 400 } };
    triangle_2->attribute["color"] = std::vector<glm::vec4>{ { 0, 0.5, 0, 0.9 }, { 0, 0.5, 0, 0.7 }, { 0, 0.5, 0, 0.9 } };
    triangle_2->uniform["transformation"] = glm::mat3(1);
    */


    msaa_resolver = std::make_unique<ShaderState>(*ShaderManager::get("resolveMSAA"));

    msaa_resolver->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
    msaa_resolver->static_uniform["amount"] = 8;


    shape.translate(100, 100);
    shape.set_line_width(2);

    render_texture = std::make_unique<ShaderState>(*ShaderManager::get("renderFBO"));

    render_texture->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
    render_texture->static_uniform["viewport"] = glm::ivec2(640, 480);


    frame_buffer_1.add_texture(Texture::Type::MULTI_SAMPLED_8, GL_RGBA8, GL_COLOR_ATTACHMENT0);
    frame_buffer_1.get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
    frame_buffer_1.get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);

    frame_buffer_2.add_texture(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA8, GL_COLOR_ATTACHMENT0);
    frame_buffer_2.get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
    frame_buffer_2.get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);


}




Renderer::~Renderer()
{
    ShaderManager::free_all();
}


void Renderer::render_frame()
{

    static float rotation = 0;

    rotation += 0.01;

    // First draw objects to multi sampled framebuffer.

    frame_buffer_1.start_rendering();

    // Clearing the framebuffer 
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shape.rotate(0.01);
    shape.render();
    //triangle_1->activate();
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    //triangle_2->activate();
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    frame_buffer_1.stop_rendering();



    msaa_resolver->activate();


    glActiveTexture(GL_TEXTURE0);
    frame_buffer_1.get_texture(0).bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    /*
    frame_buffer_2.start_rendering();

    render_texture->activate();

    frame_buffer_2.stop_rendering();
    



    // Here do mixing etc



    // Finally render the result to the screen.
    // ( No framebuffer is bound )

    //frame_buffer_2.stop_rendering();

    glClearColor(0, 0, 0.5, 1);

    render_texture->activate();

    glActiveTexture(GL_TEXTURE0);
    blurred_fbo->get_texture(0).bind();
    //frame_buffer_2.get_texture(0).bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);


    frame_buffer_1.get_texture(0).bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    */
}




void Renderer::resized(int w, int h)
{
    blur_filter.window_resized(w, h);

    frame_buffer_1.stop_rendering();
    frame_buffer_2.stop_rendering();

    glViewport(0, 0, w, h);

    frame_buffer_1.set_size(w, h);
    frame_buffer_2.set_size(w, h);

    ShaderManager::get("default")->static_uniform["viewport"] = glm::vec2(w, h);
    ShaderManager::get("renderFBO")->static_uniform["viewport"] = glm::vec2(w, h);
}
