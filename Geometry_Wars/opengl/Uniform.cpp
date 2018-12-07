#include "Uniform.h"
#include "Shader.h"
#include "ShaderState.h"



Uniform::Uniform(const UniformDefinition& def)
    : definition(def)
{
    data_pointer = new DataComponent[num_components(definition.type)];
}



Uniform::Uniform(Uniform&& other)
    : definition(other.definition)
{
    data_pointer = other.data_pointer;
    other.data_pointer = nullptr;
}



Uniform::~Uniform()
{
    if (data_pointer)
    {
        delete[] data_pointer;
    }
}



void Uniform::upload()
{
    assert(definition.location != -1);

    switch (definition.type)
    {
    case Type::FLOAT:
        glUniform1f(definition.location, data_pointer[0].f_value);
        break;

    case Type::VEC2:
        glUniform2fv(definition.location, 1, (const GLfloat *) data_pointer);
        break;

    case Type::VEC3:
        glUniform3fv(definition.location, 1, (const GLfloat *) data_pointer);
        break;

    case Type::VEC4:
        glUniform4fv(definition.location, 1, (const GLfloat *) data_pointer);
        break;


    case Type::INT:
        glUniform1i(definition.location, data_pointer[0].i_value);
        break;

    case Type::IVEC2:
        glUniform2iv(definition.location, 1, (const GLint *) data_pointer);
        break;

    case Type::IVEC3:
        glUniform3iv(definition.location, 1, (const GLint *) data_pointer);
        break;

    case Type::IVEC4:
        glUniform4iv(definition.location, 1, (const GLint *) data_pointer);
        break;


    case Type::UINT:
        glUniform1ui(definition.location, data_pointer[0].u_value);
        break;

    case Type::UVEC2:
        glUniform2uiv(definition.location, 1, (const GLuint *) data_pointer);
        break;

    case Type::UVEC3:
        glUniform3uiv(definition.location, 1, (const GLuint *) data_pointer);
        break;

    case Type::UVEC4:
        glUniform4uiv(definition.location, 1, (const GLuint *) data_pointer);
        break;


    case Type::BOOL:
        glUniform1i(definition.location, data_pointer[0].i_value);
        break;

    case Type::BVEC2:
        glUniform2iv(definition.location, 1, (const GLint *) data_pointer);
        break;

    case Type::BVEC3:
        glUniform3iv(definition.location, 1, (const GLint *) data_pointer);
        break;

    case Type::BVEC4:
        glUniform4iv(definition.location, 1, (const GLint *) data_pointer);
        break;


    case Type::MAT_2x2:
        glUniformMatrix2fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;

    case Type::MAT_2x3:
        glUniformMatrix2x3fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;

    case Type::MAT_2x4:
        glUniformMatrix2x4fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;


    case Type::MAT_3x2:
        glUniformMatrix3x2fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;

    case Type::MAT_3x3:
        glUniformMatrix3fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;

    case Type::MAT_3x4:
        glUniformMatrix3x4fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;


    case Type::MAT_4x2:
        glUniformMatrix4x2fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;

    case Type::MAT_4x3:
        glUniformMatrix4x3fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;

    case Type::MAT_4x4:
        glUniformMatrix4fv(definition.location, 1, GL_FALSE, (const GLfloat *) data_pointer);
        break;
    }
}
