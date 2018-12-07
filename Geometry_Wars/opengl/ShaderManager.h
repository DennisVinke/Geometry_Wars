#pragma once

#include <map>
#include <string>
#include <memory>

#include "Shader.h"




class ShaderManager
{

public:

    static Shader * add_shader(const std::string& name);

    static Shader * get(const std::string& name);

    static void free_all();


private:

    static std::map<std::string, std::unique_ptr<Shader>> shaders;


};