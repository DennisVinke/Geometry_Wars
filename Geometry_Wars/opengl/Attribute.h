#pragma once

#include <map>
#include <deque>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "AttributeDefinition.h"
#include "types.h"


class ShaderState;




/// class Attribute: Represents an attribute in an OpenGL shader program.
/**
 * Attributes specify the input that is passed to OpenGL shaders from the cpu side.
 * The type of the attribute is given by its AttributeDefinition, the only argument
 * to Attribute's constructor.
 */
class Attribute
{

public:

    // Default constructor is deleted so that Attributes always have a type and definition.
    Attribute() = delete;

    // Copying of an Attribute would be confusing, since it would create multiple references to a gpu resource.
    Attribute(const Attribute&) = delete;

    /// Move constructor of Attribute. Moving of an Attribute is defined, because always only a single reference to
    /// the gpu resources exists. 
    Attribute(Attribute&& other);

    /// Attributes can only be created from an existing AttributeDefinition.
    Attribute(const AttributeDefinition& definition);

    /// Destructor for Attribute.
    ~Attribute();


    /// The values stored on the grphis card that will be used as the vertex attributes for draw calls on the current
    /// ShaderState, can be set using the assignment operator. This will upload the data to OpenGL, in a vertex buffer.
    template<typename T>
    void operator=(const std::vector<T>& data);

    /// Returns the raw vbo handle as used by OpenGL.
    GLuint get_handle() const;


    /// The AttributeDefinition, this Attribute refers to.
    const AttributeDefinition& definition;


private:

    bool has_moved = true;

    unsigned int num_allocated = 0;

    GLuint vbo_handle;

};




template<typename T>
void Attribute::operator=(const std::vector<T>& data)
{
    //assert(definition.type == reduce_type<T>::value);
    // TODO think about assert.

    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);

    if (num_allocated < data.size())
    {
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_DYNAMIC_DRAW);
        num_allocated = data.size();
    }
    else
    {
        glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(T), data.data());
    }
}
