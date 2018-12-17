#pragma once

#include <map>
#include <string>
#include <memory>

#include "opengl/Shader.h"



/// class ShaderManager: used to keep track of current running shaders
/*
 * ShaderManager holds a map of shaders, that can be added with a name, and
 * be retrieved from anywhere in the program. Even though this class is 
 * implemented as a class, all its methods are static, which means it behaves pretty 
 * much the same as a namespace. It is implemented this way, because there never is
 * a reason to load shaders more than once.
 */
class ShaderManager
{

public:

    /// Adds a new Shader, with a name, can be retrieved from anywhere in the program.
    static Shader * add_shader(const std::string& name);

    /// Retrieve a Shader from a name, nullptr, if that Shader doesn't exist.
    static Shader * get(const std::string& name);

    /// Used to deallocate all the shaders, necesary because this class has no destructor.
    static void free_all();

    
    static void load_default_shader();
    static void load_horizontalBlur_shader();
    static void load_verticalBlur_shader();
    static void load_renderFBO_shader();
    static void load_resolveMSAA_shader();


private:

    static std::map<std::string, std::unique_ptr<Shader>> shaders;


};