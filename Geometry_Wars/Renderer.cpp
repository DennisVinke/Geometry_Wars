

#include "glm_type_registration.h"

#include "Shape.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "RenderComponent.h"
#include "random.h"
#include "Background.h"

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

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    

    auto [path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    if (fs::exists(shaders_folder) && fs::is_directory(shaders_folder))
    {
        std::cout << "\nShaders folder found at:\n";
        std::cout << shaders_folder << '\n';
    }
    else
    {
        std::cout << "\nUnable to locate \'shaders\' folder.";
    }


    msaa_resolver = std::make_unique<ShaderState>(*ShaderManager::get("resolveMSAA"));
    msaa_resolver->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
    msaa_resolver->static_uniform["amount"] = 8;


    combine_shader = std::make_unique<ShaderState>(*ShaderManager::get("combine"));
    combine_shader->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };




    std::vector<glm::vec2> s{ {-10, -10}, { -10, 10 }, { 10, 10}, { 10, -10} };

    for (auto& shape : test_shapes)
    {
        shape.set_shape(s);
        shape.translate(random(0, 500), random(0, 500));
        shape.rotate(random(30.0f));
        shape.scale(random(1.0f, 5.0f), random(1.0f, 5.0f));
        shape.set_color(random(255), 150, 200, 255);
        //shape.set_line_width(random(3, 20));
        shape.set_line_width(3);
    }

    render_texture = std::make_unique<ShaderState>(*ShaderManager::get("renderFBO"));

    render_texture->attribute["position"] = std::vector<glm::vec2>{ {-1, 1 }, { 1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 }, { -1, -1 } };
    render_texture->static_uniform["viewport"] = glm::ivec2(640, 480);


    frame_buffer_1.add_texture(Texture::Type::MULTI_SAMPLED_8, GL_RGBA8, GL_COLOR_ATTACHMENT0);
    frame_buffer_1.get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
    frame_buffer_1.get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);

    frame_buffer_2.add_texture(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA8, GL_COLOR_ATTACHMENT0);
    frame_buffer_2.get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
    frame_buffer_2.get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);
    
    combined_blur.add_texture(Texture::Type::NORMALIZED_NO_MIPMAP, GL_RGBA8, GL_COLOR_ATTACHMENT0);
    combined_blur.get_texture(0).set_wrap_x(GL_CLAMP_TO_EDGE);
    combined_blur.get_texture(0).set_wrap_y(GL_CLAMP_TO_EDGE);

    background = std::make_unique<Background>();
}




Renderer::~Renderer()
{
    ShaderManager::free_all();
}


void Renderer::render_frame()
{

    // First draw objects to multi sampled framebuffer.

    frame_buffer_1.start_rendering();

    // Clearing the framebuffer 
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    background->render();

	for (auto renderable : renderables) 
    {
		renderable->render();
	}
	renderables.clear();

    for (auto& shape : test_shapes)
    {
        shape.rotate(0.01);
        shape.render();
    }


    frame_buffer_1.stop_rendering();

    // ***************************************************************


    frame_buffer_2.start_rendering();

    msaa_resolver->activate();


    glActiveTexture(GL_TEXTURE0);
    frame_buffer_1.get_texture(0).bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    frame_buffer_2.stop_rendering();

    // ***************************************************************

    auto near_blur = blur_near.apply(frame_buffer_2.get_texture(0));
    auto far_blur = blur_far.apply(frame_buffer_2.get_texture(0));

    combined_blur.start_rendering();

    combine_shader->activate();


    glUniform1i(glGetUniformLocation(combine_shader->get_shader().get_handle(), "tex1"), 0);
    glUniform1i(glGetUniformLocation(combine_shader->get_shader().get_handle(), "tex2"), 1);


    glActiveTexture(GL_TEXTURE0);
    near_blur->get_texture(0).bind();

    glActiveTexture(GL_TEXTURE1);
    far_blur->get_texture(0).bind();

    combine_shader->uniform["weights"] = glm::vec2(0.7, 0.7);


    glDrawArrays(GL_TRIANGLES, 0, 6);

    combined_blur.stop_rendering();

    // ***************************************************************


    auto original_texture = &(frame_buffer_2.get_texture(0));
    auto blurred_texture = &combined_blur.get_texture(0);

    combine_shader->activate();

    glActiveTexture(GL_TEXTURE0);
    blurred_texture->bind();

    glActiveTexture(GL_TEXTURE1);
    original_texture->bind();

    combine_shader->uniform["weights"] = glm::vec2(3, 1);


    glDrawArrays(GL_TRIANGLES, 0, 6);


    background->render_welcome_screen();

    //background->render();

    //combine_shader->activate();
    //render_texture->activate();


    //glUniform1i(glGetUniformLocation(combine_shader->get_shader().get_handle(), "tex1"), 0);
    //glUniform1i(glGetUniformLocation(combine_shader->get_shader().get_handle(), "tex2"), 1);

    /*
    glActiveTexture(GL_TEXTURE0);
    near_blur->get_texture(0).bind();

    glActiveTexture(GL_TEXTURE1);
    original_texture->bind();
    */



    //int texture_units = 0;
    //glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);

    //std::cout << texture_units << std::endl;

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
    background->window_resized(w, h);

    blur_near.window_resized(w, h);
    blur_far.window_resized(w, h);

    frame_buffer_1.stop_rendering();
    frame_buffer_2.stop_rendering();
    combined_blur.stop_rendering();

    glViewport(0, 0, w, h);

    frame_buffer_1.set_size(w, h);
    frame_buffer_2.set_size(w, h);
    combined_blur.set_size(w, h);

    ShaderManager::get("default")->static_uniform["viewport"] = glm::vec2(w, h);
    ShaderManager::get("renderFBO")->static_uniform["viewport"] = glm::vec2(w, h);
    ShaderManager::get("combine")->static_uniform["viewport"] = glm::vec2(w, h);
}

void Renderer::queueToRender(RenderComponent * component)
{
	renderables.emplace_back(component);
}
