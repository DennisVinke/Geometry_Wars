#include "Shader.h"



Shader::Shader()
{
    program_handle = glCreateProgram();
}


Shader::~Shader()
{
    for (auto shader : shader_stage_handles)
    {
        glDeleteShader(shader);
    }

    glDeleteProgram(program_handle);
}


bool Shader::add_stage(const std::string& source, GLenum shader_type)
{
    GLuint shader_handle = glCreateShader(shader_type);

    // (const GLchar * const *) 

    const char* src = source.c_str();

    glShaderSource(shader_handle, 1, &src, nullptr);
    glCompileShader(shader_handle);

    GLint success;
    char info_log[512];

    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);

    if (success == GL_TRUE)
    {
        shader_stage_handles.push_back(shader_handle);
        return true;
    }
    else
    {
        glGetShaderInfoLog(shader_handle, 512, nullptr, info_log);
        glDeleteShader(shader_handle);
        std::cout << "Shader compilation failure:\n\n" << info_log << "\n\n";
        return false;
    }
}


bool Shader::compile()
{
    for (GLuint shader : shader_stage_handles)
    {
        glAttachShader(program_handle, shader);
    }

    glLinkProgram(program_handle);

    GLint success;
    char info_log[512];

    glGetProgramiv(program_handle, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program_handle, 512, nullptr, info_log);
        std::cout << "Shader linking failure:\n\n" << info_log << "\n\n";
    }
    return success == GL_TRUE;
}


void Shader::start()
{
    glUseProgram(program_handle);
}


void Shader::stop()
{
    glUseProgram(0);
}



void Shader::set_uniform_1f(const std::string& name, const float& value)
{
    glUniform1fv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLfloat*>(&value));
}

void Shader::set_uniform_2f(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLfloat*>(&value[0]));
}

void Shader::set_uniform_3f(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLfloat*>(&value[0]));
}

void Shader::set_uniform_4f(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLfloat*>(&value[0]));
}




void Shader::set_uniform_1i(const std::string& name, const int& value)
{
    glUniform1iv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLint*>(&value));
}

void Shader::set_uniform_2i(const std::string& name, const glm::ivec2& value)
{
    glUniform2iv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLint*>(&value[0]));
}

void Shader::set_uniform_3i(const std::string& name, const glm::ivec3& value)
{
    glUniform3iv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLint*>(&value[0]));
}

void Shader::set_uniform_4i(const std::string& name, const glm::ivec4& value)
{
    glUniform4iv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLint*>(&value[0]));
}



void Shader::set_uniform_1u(const std::string& name, const unsigned int& value)
{
    glUniform1uiv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLuint*>(&value));
}

void Shader::set_uniform_2u(const std::string& name, const glm::uvec2& value)
{
    glUniform2uiv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLuint*>(&value[0]));
}

void Shader::set_uniform_3u(const std::string& name, const glm::uvec3& value)
{
    glUniform3uiv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLuint*>(&value[0]));
}

void Shader::set_uniform_4u(const std::string& name, const glm::uvec4& value)
{
    glUniform4uiv(glGetUniformLocation(program_handle, name.c_str()), 1, static_cast<const GLuint*>(&value[0]));
}



void Shader::set_uniform_mat2x2(const std::string& name, const glm::mat2x2& value)
{
    glUniformMatrix2fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}

void Shader::set_uniform_mat2x3(const std::string& name, const glm::mat2x3& value)
{
    glUniformMatrix2x3fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}

void Shader::set_uniform_mat2x4(const std::string& name, const glm::mat2x4& value)
{
    glUniformMatrix2x4fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}



void Shader::set_uniform_mat3x2(const std::string& name, const glm::mat3x2& value)
{
    glUniformMatrix3x2fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}

void Shader::set_uniform_mat3x3(const std::string& name, const glm::mat3x3& value)
{
    glUniformMatrix3fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}

void Shader::set_uniform_mat3x4(const std::string& name, const glm::mat3x4& value)
{
    glUniformMatrix3x4fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}



void Shader::set_uniform_mat4x2(const std::string& name, const glm::mat4x2& value)
{
    glUniformMatrix4x2fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}

void Shader::set_uniform_mat4x3(const std::string& name, const glm::mat4x3& value)
{
    glUniformMatrix4x3fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}

void Shader::set_uniform_mat4x4(const std::string& name, const glm::mat4x4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(program_handle, name.c_str()), 1, false, static_cast<const GLfloat*>(&value[0][0]));
}


/*
void add_transform_feedback(std::initializer_list<std::string> transform_feedback, GLenum mode = GL_SEPARATE_ATTRIBS)
{
    std::vector<const char*> strings;

    for (auto& s : transform_feedback)
    {
        strings.push_back(s.c_str());
    }

    glTransformFeedbackVaryings(program_handle, strings.size(), (const GLchar * const *)strings.data(), mode);
}
*/