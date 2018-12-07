#pragma once

#include <string>

#include <glad/glad.h>

#include "types.h"




/// class UniformDefinition: specifies the Existence and signature of an uniform variable in 
/// an OpenGl Shader program.
struct UniformDefinition
{
    UniformDefinition(const std::string& name_, const Type& type_)
        : name(name_), type(type_)
    { }

    UniformDefinition(const UniformDefinition&) = delete;

    UniformDefinition(UniformDefinition&&) = delete;


    const std::string name;
    const Type type;

    GLint location = -1;
};
