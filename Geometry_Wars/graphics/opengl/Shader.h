#pragma once

#include <list>
#include <map>
#include <vector>
#include <memory>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "AttributeDefinition.h"
#include "UniformDefinition.h"
#include "Uniform.h"
#include "MapView.h"

#include "types.h"


class ShaderState;




/// Shader class, represents an OpenGL shader program.
/** 
 * This class represents a shader program in OpenGL.
 * The OpenGL state represented by this class is mostly immutable, 
 * and should be modified through the ShaderState class.
 * The layout of the shader can be specified, which will only effect
 * ShaderState's that are produced with this shader.
 */
class Shader
{
    friend class ShaderState;


public:

    /// Default constructor for the Shader class.
    Shader();

    /// Destructor for Shader class.
    ~Shader();

    // We no copy.
    Shader(const Shader&) = delete;

    /// No moving either, no point in moving this class, just allocate on the heap
    Shader(Shader&&) = delete;


    /// Allows the user to specify the existence of an Attribute in the shader source code.
    /// This does not allow you to change anything in an Attribute, for this you need to create
    /// a ShaderState object using this shader.
    void add_attribute(int index, const std::string& name, Type type, bool normalize_ints = false);

    /// Allows the user to specify the existence of a Uniform in the shader source code.
    /// This does not allow you to change the value of the Uniform variable, for this you need to create
    /// a ShaderState object using this shader.
    void add_uniform(const std::string& name, Type type);

    /// Allows the user to specify the existence of a Uniform in the shader source code. which holds
    /// the same value for all ShaderState objects. This is the only gpu side state stored in this class,
    /// simply because it should not be part of ShaderState.
    void add_static_uniform(const std::string& name, Type type);


    /// Adds a ShaderStage to the Shader, shader_type denotes the type of this stage IE. GL_VERTEX_SHADER
    /// or GL_FRAGMENT_SHADER. The source code is given in a std::string, and compiled by the graphics driver.
    bool add_shader_stage(const std::string& source, GLenum shader_type);

    /// Links the added stages together, and creates a finished program that can be used for rendering.
    bool compile();

    /// Returns the raw OpenGL handle, that holds the reference to the OpenGL shader. Only use this method
    /// if you know what your are doing!
    GLuint get_handle() const;


    MapView<std::string, Uniform> static_uniform{ static_uniforms };


private:

    // Sets this to be the current active Shader, for use by ShaderState.
    void activate();

    // Checks if this is the current active Shader, for use by ShaderState.
    bool is_active();

    // OpenGL handle for the complete shader program.
    GLuint program_handle;

    // OpenGL handles for the individual stages of the shader program.
    std::vector<GLuint> shader_stage_handles;


    // std::list guarantees pointer persistence.
    // This means that the attributes and uniforms that will be made only need
    // a pointer to their respective definition, and it will be guaranteed to
    // never change. if I.E. std::vector was used all elements could be placed
    // elsewhere in memory, when adding to the back of the vector.
    std::vector<std::unique_ptr<AttributeDefinition>> attribute_definitions;

    std::vector<std::unique_ptr<UniformDefinition>> uniform_definitions;
    std::vector<std::unique_ptr<UniformDefinition>> static_uniform_definitions;

    // static_uniforms are the only gpu side state in the Shader class.
    std::map<std::string, Uniform> static_uniforms;


    // Used from within ShaderState.
    ShaderState* currently_active_state = nullptr;


    // Keeps track of the current active Shader.
    static Shader* current_shader;


};
