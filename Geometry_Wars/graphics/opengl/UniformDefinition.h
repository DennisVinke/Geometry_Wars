#pragma once

#include <string>

#include <glad/glad.h>

#include "types.h"



/// class UniformDefinition: specifies the Existence and signature of an uniform variable in 
/// an OpenGl Shader program.
class UniformDefinition
{
    friend class Shader;


public:

    const std::string name;

    const Type type;

    const Shader& shader;


    int get_location() const { return location; }

    bool is_static() const { return b_is_static; }


private:

    UniformDefinition(const std::string& name_, const Type& type_, const Shader& shader_)
        : name(name_), type(type_), shader(shader_)
    { }

    UniformDefinition(const UniformDefinition&) = delete;

    UniformDefinition(UniformDefinition&&) = delete;


    bool b_is_static = false;

    GLint location = -1;

};
