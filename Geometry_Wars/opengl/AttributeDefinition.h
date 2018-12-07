#pragma once

#include <string>

#include "types.h"




/// class AttributeDefinition: specifies the Existence and signature of an attribute in 
/// an OpenGl Shader program.
struct AttributeDefinition
{
    AttributeDefinition() = delete;

    const int index;
    const std::string name;
    const Type type;
    const bool normalize_integers = false;
};
