#pragma once

#include <string>

#include "types.h"



class Shader;


/// class AttributeDefinition: specifies the Existence and signature of an attribute in 
/// an OpenGl Shader program.
class AttributeDefinition
{

    friend class Shader;

public:


    const int index;
    
    const std::string name;
    
    const Type type;
    
    const bool normalize_ints;

    const Shader& shader;


private:


    AttributeDefinition(int index_, const std::string& name_, Type type_, bool normalize_ints_, const Shader& shader_)
        : index(index_), name(name_), type(type_), normalize_ints(normalize_ints_), shader(shader_)
    { }

    AttributeDefinition(const AttributeDefinition&) = delete;

    AttributeDefinition(AttributeDefinition&&) = delete;



};
