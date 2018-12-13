#pragma once

#include <glad/glad.h>

#include "Attribute.h"
#include "Uniform.h"
#include "MapView.h"



class Shader;





/// class ShaderState: Allows the user to adjust the state of an OpenGL Shader.
/**
 * This class holds two views, one to a map of uniforms, and one to a map of attributes.
 * these correspond to the state of a shader that can be set by the user. This class changes 
 * how the user interacts with shaders, instead of all state being global, as is usual in OpenGL
 * By creating a ShaderState one can safe a state of the Shader, and edit its properties, without
 * having to reconfigure every variable. When the activate method is called the state represented
 * by ShaderState will be send to OpenGL.
 */
class ShaderState
{

public:

    // ShaderState can only be constructed from an existing Shader.
    ShaderState() = delete;

    // No copying allowed!
    ShaderState(const ShaderState&) = delete;

    /// Moving ShaderState is okay, only one vesion keeps alive.
    ShaderState(ShaderState&&);

    /// ShaderState can only be constructed from an existing Shader object.
    /// during construction ShaderState creates variables for the uniforms and
    /// attributes defined in the Shader.
    ShaderState(Shader& shader);

    /// Destructor for ShaderState.
    ~ShaderState();


    /// When activated all the variables stored in the ShaderState are made current,
    /// This means that You do not need to reupload all the ShaderState variables each time
    /// you want to render the same object in the same way.
    void activate();

    /// Checks whether this SHaderState is the current active ShaderState.
    bool is_active() const;

    /// Returns the Shader instance this ShaderState changes the state of.
    const Shader& get_shader() const;

    /// Allows the user to access the uniforms in the map, without changing the map itself.
    MapView<std::string, Uniform> uniform{ uniforms };

    /// Allows the user to access the attributes in the map, without changing the map itself.
    MapView<std::string, Attribute> attribute{ attributes };

    /// Allows the user to access the static uniforms in the map, without changing the map itself.
    MapView<std::string, Uniform> static_uniform;


private:

    bool cleanup_responsible = true;

    Shader& shader;

    GLuint vao_handle;

    std::map<std::string, Uniform> uniforms;
    std::map<std::string, Attribute> attributes;

};
