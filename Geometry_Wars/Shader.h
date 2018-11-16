#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "NoCopy.h"
#include "NoMove.h"



class Shader : public NoCopy,
               public NoMove
{

public:

    Shader();

    virtual ~Shader();

    void start();

    void stop();


    void set_uniform_1f(const std::string& name, const float& value);
    void set_uniform_2f(const std::string& name, const glm::vec2& value);
    void set_uniform_3f(const std::string& name, const glm::vec3& value);
    void set_uniform_4f(const std::string& name, const glm::vec4& value);

    void set_uniform_1i(const std::string& name, const int& value);
    void set_uniform_2i(const std::string& name, const glm::ivec2& value);
    void set_uniform_3i(const std::string& name, const glm::ivec3& value);
    void set_uniform_4i(const std::string& name, const glm::ivec4& value);

    void set_uniform_1u(const std::string& name, const unsigned int& value);
    void set_uniform_2u(const std::string& name, const glm::uvec2& value);
    void set_uniform_3u(const std::string& name, const glm::uvec3& value);
    void set_uniform_4u(const std::string& name, const glm::uvec4& value);

    void set_uniform_mat2x2(const std::string& name, const glm::mat2x2& value);
    void set_uniform_mat2x3(const std::string& name, const glm::mat2x3& value);
    void set_uniform_mat2x4(const std::string& name, const glm::mat2x4& value);

    void set_uniform_mat3x2(const std::string& name, const glm::mat3x2& value);
    void set_uniform_mat3x3(const std::string& name, const glm::mat3x3& value);
    void set_uniform_mat3x4(const std::string& name, const glm::mat3x4& value);

    void set_uniform_mat4x2(const std::string& name, const glm::mat4x2& value);
    void set_uniform_mat4x3(const std::string& name, const glm::mat4x3& value);
    void set_uniform_mat4x4(const std::string& name, const glm::mat4x4& value);



    bool add_stage(const std::string& source, GLenum shader_type);

    bool compile();


protected:


    GLuint program_handle;

    std::vector<GLuint> shader_stage_handles;


};
