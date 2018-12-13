#pragma once

#include <map>
#include <string>
#include <memory>

#include "opengl/Shader.h"




class ShaderManager
{

public:

    static Shader * add_shader(const std::string& name);

    static Shader * get(const std::string& name);

    static void free_all();


    static void load_default_shader();
    static void load_horizontalBlur_shader();
    static void load_verticalBlur_shader();
    static void load_renderFBO_shader();
    static void load_resolveMSAA_shader();


private:

    static std::map<std::string, std::unique_ptr<Shader>> shaders;


};