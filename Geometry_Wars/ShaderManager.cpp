
#include "glm_type_registration.h"

#include "ShaderManager.h"




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
