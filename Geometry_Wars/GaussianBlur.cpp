#include "GaussianBlur.h"
#include "ShaderManager.h" 

#include "io/load_file_to_string.h"

#include "opengl/Shader.h"
#include "opengl/ShaderState.h"

#include <cassert>





void GaussianBlur::load_shaders()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";



    auto hor = ShaderManager::add_shader("horizontalBlur");

    hor->add_shader_stage(load_file_to_string(shaders_folder / "minimal2D.vert"), GL_VERTEX_SHADER);
    hor->add_shader_stage(load_file_to_string(shaders_folder / "horizontalBlur.frag"), GL_FRAGMENT_SHADER);

    hor->add_attribute(0, "position", Type::VEC2);
    hor->add_static_uniform("blur_amount", Type::INT);
    hor->add_static_uniform("window_width", Type::INT);
    hor->add_static_uniform("window_height", Type::INT);

    hor->compile();



    auto vert = ShaderManager::add_shader("verticalBlur");

    vert->add_shader_stage(load_file_to_string(shaders_folder / "minimal2D.vert"), GL_VERTEX_SHADER);
    vert->add_shader_stage(load_file_to_string(shaders_folder / "verticalBlur.frag"), GL_FRAGMENT_SHADER);

    vert->add_attribute(0, "position", Type::VEC2);
    vert->add_static_uniform("blur_amount", Type::INT);
    vert->add_static_uniform("window_width", Type::INT);
    vert->add_static_uniform("window_height", Type::INT);

    vert->compile();
}






GaussianBlur::GaussianBlur(unsigned int w, unsigned int h, float rel_size, unsigned int n_it)
    : relative_size_per_iteration(rel_size), n_iterations(n_it)
{
    assert(relative_size_per_iteration >= 0.5f && relative_size_per_iteration <= 1.0f);
    assert(n_it > 0 && n_it <= 10);  // more than 10 seems excessive;
    
    float width = w;
    float height = h;

    frame_buffers.reserve(n_iterations * 2);

    for (int i = 0; i < n_iterations; ++i)
    {
        width *= relative_size_per_iteration;
        height *= relative_size_per_iteration;

        frame_buffers.emplace_back(width, height);
        frame_buffers.back().add_texture(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA, GL_COLOR_ATTACHMENT0);
        frame_buffers.back().get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
        frame_buffers.back().get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);

        frame_buffers.emplace_back(width, height);
        frame_buffers.back().add_texture(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA, GL_COLOR_ATTACHMENT0);
        frame_buffers.back().get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
        frame_buffers.back().get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);
    }


    horizontal = std::make_unique<ShaderState>(*ShaderManager::get("horizontalBlur"));
    horizontal->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
    horizontal->static_uniform["blur_amount"] = 4;

    vertical = std::make_unique<ShaderState>(*ShaderManager::get("verticalBlur"));
    vertical->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
    vertical->static_uniform["blur_amount"] = 4;
}





void GaussianBlur::window_resized(unsigned int w, unsigned int h)
{
    float width = w;
    float height = h;

    for (int i = 0; i < frame_buffers.size(); ++i)
    {
        width *= relative_size_per_iteration;
        height *= relative_size_per_iteration;

        frame_buffers[i].set_size(width, height); 

        //frame_buffers[i + 1].set_size(width, height);
    }
}


FrameBuffer* GaussianBlur::apply(const Texture& texture)
{
    const Texture* tex_ptr = &texture;

    for (int i = 0; i < frame_buffers.size(); i += 2)
    {
        frame_buffers[i].start_rendering();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        horizontal->activate();
        horizontal->static_uniform["window_width"] = frame_buffers[i].get_width();
        horizontal->static_uniform["window_height"] = frame_buffers[i].get_height();

        glActiveTexture(GL_TEXTURE0);
        tex_ptr->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        frame_buffers[i].stop_rendering();

        tex_ptr = &frame_buffers[i].get_texture(0);
        
        //*******************************************************************************

        frame_buffers[i + 1].start_rendering();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        vertical->activate();
        vertical->static_uniform["window_width"] = frame_buffers[i + 1].get_width();
        vertical->static_uniform["window_height"] = frame_buffers[i + 1].get_height();

        glActiveTexture(GL_TEXTURE0);
        tex_ptr->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        frame_buffers[i + 1].stop_rendering();

        tex_ptr = &frame_buffers[i + 1].get_texture(0);
    }

    return &frame_buffers.back();
}



FrameBuffer* GaussianBlur::debug(const Texture& texture)
{

    const Texture* tex_ptr = &texture;

    frame_buffers[0].start_rendering();

    horizontal->activate();
    horizontal->static_uniform["window_width"] = frame_buffers[0].get_width();
    horizontal->static_uniform["window_height"] = frame_buffers[0].get_height();

    glActiveTexture(GL_TEXTURE0);
    tex_ptr->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    frame_buffers[0].stop_rendering();

    tex_ptr = &frame_buffers[0].get_texture(0);

    
    frame_buffers[1].start_rendering();

    vertical->activate();
    vertical->static_uniform["window_width"] = frame_buffers[1].get_width();
    vertical->static_uniform["window_height"] = frame_buffers[1].get_height();

    glActiveTexture(GL_TEXTURE0);
    tex_ptr->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    frame_buffers[1].stop_rendering();


    /////////////////

    return &frame_buffers[1];
}
