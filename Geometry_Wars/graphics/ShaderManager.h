#pragma once

#include <map>
#include <string>
#include <memory>

#include "opengl/Shader.h"



/// class ShaderManager: used to keep track of current running shaders
/**
 * ShaderManager holds a map of shaders, that can be added with a name, and
 * be retrieved from anywhere in the program. Even though this class is 
 * implemented as a class, all its methods are static, which means it behaves pretty 
 * much the same as a namespace. It is implemented this way, because there never is
 * a reason to load shaders more than once.
 */
class ShaderManager
{

public:

    /// add_shader()
    /**
     *  static function that addd a new Shader, with a name, so that it can be retrieved 
     *  from anywhere in the program.
     */
    static Shader * add_shader(const std::string& name);


    /// get()
    /**
     *  get allows you to retrieve the address of a shader with a name anywhere in the code.
     *  If there is no shader with that name then a nullptr will be returned.
     */
    static Shader * get(const std::string& name);


    /// shutdown();
    /**
     *  function that should be closed when the aplciation is closed. This makes sure all the
     *  resources held by the ShaderManager are released, and the program can safely be closed.
     *  This fucntion is necessary because this is a static class and we can thus not use RAII.
     */
    static void shutdown();


    /// initialize()
    /**
     *  Static function that initializes some default shaders, and makes this class usable.
     */
    static void initialize();


private:

    static std::map<std::string, std::unique_ptr<Shader>> shaders;


    static void load_default_shader();
    static void load_horizontalBlur_shader();
    static void load_verticalBlur_shader();
    static void load_combine_shader();
    static void load_renderFBO_shader();
    static void load_resolveMSAA_shader();
    static void load_background_shader();
    static void load_texture_shader();
    static void load_final_shader();

};