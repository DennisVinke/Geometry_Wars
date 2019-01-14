
#include "glm_type_registration.h"

#include "ShaderManager.h"
#include "io/load_file_to_string.h"



std::map<std::string, std::unique_ptr<Shader>> ShaderManager::shaders;


Shader* ShaderManager::add_shader(const std::string& name)
{
    Shader* shader = new Shader();
    shaders[name] = std::unique_ptr<Shader>(shader);
    return shader;
}


Shader* ShaderManager::get(const std::string& name)
{
    return shaders.at(name).get();
}


void ShaderManager::free_all()
{
    shaders.clear();
}



void ShaderManager::load_shaders()
{
    load_default_shader();
    load_renderFBO_shader();
    load_resolveMSAA_shader();
    load_combine_shader();
    load_background_shader();
    load_texture_shader();
    load_final_shader();
}



void ShaderManager::load_default_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto default_shader = ShaderManager::add_shader("default");

    default_shader->add_shader_stage(load_file_to_string(shaders_folder / "default.vert"), GL_VERTEX_SHADER);
    default_shader->add_shader_stage(load_file_to_string(shaders_folder / "default.frag"), GL_FRAGMENT_SHADER);

    default_shader->add_attribute(0, "position", Type::VEC2);
    //default_shader->add_attribute(1, "color", Type::VEC4);

    default_shader->add_uniform("transformation", Type::MAT_3x3);
    default_shader->add_static_uniform("viewport", Type::VEC2);
    default_shader->add_uniform("color", Type::VEC4);



    default_shader->compile();
}


void ShaderManager::load_horizontalBlur_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";


}


void ShaderManager::load_verticalBlur_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

}


void ShaderManager::load_combine_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto combine_shader = ShaderManager::add_shader("combine");

    combine_shader->add_shader_stage(load_file_to_string(shaders_folder / "minimal2D.vert"), GL_VERTEX_SHADER);
    combine_shader->add_shader_stage(load_file_to_string(shaders_folder / "combine.frag"),     GL_FRAGMENT_SHADER);

    combine_shader->add_attribute(0, "position", Type::VEC2);
    combine_shader->add_uniform("weights", Type::VEC2);
    combine_shader->add_static_uniform("viewport", Type::IVEC2);
    
    combine_shader->compile();
}


void ShaderManager::load_final_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto final_shader = ShaderManager::add_shader("final");

    final_shader->add_shader_stage(load_file_to_string(shaders_folder / "minimal2D.vert"), GL_VERTEX_SHADER);
    final_shader->add_shader_stage(load_file_to_string(shaders_folder / "final.frag"), GL_FRAGMENT_SHADER);

    final_shader->add_attribute(0, "position", Type::VEC2);
    final_shader->add_uniform("weights", Type::VEC2);
    final_shader->add_uniform("inverted", Type::INT);
    final_shader->add_uniform("r_transform", Type::MAT_3x3);
    final_shader->add_uniform("g_transform", Type::MAT_3x3);
    final_shader->add_uniform("b_transform", Type::MAT_3x3);
    final_shader->add_static_uniform("viewport", Type::IVEC2);

    final_shader->compile();
}


void ShaderManager::load_texture_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto centred_texture_shader = ShaderManager::add_shader("texture");

    centred_texture_shader->add_shader_stage(load_file_to_string(shaders_folder / "texture.vert"), GL_VERTEX_SHADER);
    centred_texture_shader->add_shader_stage(load_file_to_string(shaders_folder / "texture.frag"), GL_FRAGMENT_SHADER);

    centred_texture_shader->add_attribute(0, "position", Type::VEC2);
    centred_texture_shader->add_attribute(1, "tex_coord", Type::VEC2);
    centred_texture_shader->add_static_uniform("viewport", Type::VEC2);

    centred_texture_shader->compile();
}


void ShaderManager::load_background_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto background_shader = ShaderManager::add_shader("background");

    background_shader->add_shader_stage(load_file_to_string(shaders_folder / "background.vert"), GL_VERTEX_SHADER);
    background_shader->add_shader_stage(load_file_to_string(shaders_folder / "background.frag"), GL_FRAGMENT_SHADER);

    background_shader->add_attribute(0, "position", Type::VEC2);
    background_shader->add_attribute(1, "color", Type::FLOAT);

    background_shader->compile();
}


void ShaderManager::load_renderFBO_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto renderFBO_shader = ShaderManager::add_shader("renderFBO");

    renderFBO_shader->add_shader_stage(load_file_to_string(shaders_folder / "minimal2D.vert"), GL_VERTEX_SHADER);
    renderFBO_shader->add_shader_stage(load_file_to_string(shaders_folder / "renderFBO.frag"), GL_FRAGMENT_SHADER);

    renderFBO_shader->add_attribute(0, "position", Type::VEC2);
    renderFBO_shader->add_static_uniform("viewport", Type::IVEC2);

    renderFBO_shader->compile();
}


void ShaderManager::load_resolveMSAA_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto resolveMSAA_shader = ShaderManager::add_shader("resolveMSAA");

    resolveMSAA_shader->add_shader_stage(load_file_to_string(shaders_folder / "minimal2D.vert"), GL_VERTEX_SHADER);
    resolveMSAA_shader->add_shader_stage(load_file_to_string(shaders_folder / "resolveMSAA.frag"), GL_FRAGMENT_SHADER);

    resolveMSAA_shader->add_attribute(0, "position", Type::VEC2);
    resolveMSAA_shader->add_static_uniform("amount", Type::INT);

    resolveMSAA_shader->compile();
}

