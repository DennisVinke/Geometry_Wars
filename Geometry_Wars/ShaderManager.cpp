
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


void ShaderManager::load_texture_shader()
{
    auto[path, success] = find_folder("Geometry_Wars");
    auto shaders_folder = path / "data";

    auto texture_shader = ShaderManager::add_shader("texture");

    texture_shader->add_shader_stage(load_file_to_string(shaders_folder / "texture.vert"), GL_VERTEX_SHADER);
    texture_shader->add_shader_stage(load_file_to_string(shaders_folder / "texture.frag"), GL_FRAGMENT_SHADER);

    texture_shader->add_attribute(0, "position", Type::VEC2);
    texture_shader->add_attribute(1, "tex_coord", Type::VEC2);
    texture_shader->add_static_uniform("viewport", Type::VEC2);

    texture_shader->compile();
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

