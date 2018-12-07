#include "Attribute.h"



Attribute::Attribute(const AttributeDefinition& definition)
    : definition(definition)
{
    glGenBuffers(1, &vbo_handle);
}



Attribute::Attribute(Attribute&& other)
    : definition(other.definition)
{
    vbo_handle = other.vbo_handle;
    num_allocated = other.num_allocated;
    other.vbo_handle = 0;
    other.has_moved = false;
}



Attribute::~Attribute()
{
    if (has_moved)
    {
        glDeleteBuffers(1, &vbo_handle);
    }
}



GLuint Attribute::get_handle() const
{
    return vbo_handle;
}
