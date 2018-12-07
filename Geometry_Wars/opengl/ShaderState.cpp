#include "ShaderState.h"
#include "Shader.h"




ShaderState::ShaderState(Shader& s)
    : shader(s), static_uniform(s.static_uniforms)
{
    for (const auto& u : shader.uniform_definitions)
    {
        uniforms.emplace(u.name, Uniform(u));
    }

    for (const auto& a : shader.attribute_definitions)
    {
        attributes.emplace(a.name, a);
    }

    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    for (auto& [name, attr] : attributes)
    {
        glBindBuffer(GL_ARRAY_BUFFER, attr.get_handle());
        glVertexAttribPointer(attr.definition.index, num_components(attr.definition.type), 
            gl_base_type(attr.definition.type), attr.definition.normalize_integers, 0, 0);
        glEnableVertexAttribArray(attr.definition.index);
    }
}



ShaderState::ShaderState(ShaderState&& other) 
    : shader(other.shader), attributes(std::move(other.attributes)), 
    uniforms(std::move(other.uniforms)), static_uniform(other.shader.static_uniforms)
{
    vao_handle = other.vao_handle;
    other.vao_handle = 0;
    other.has_moved = false;
    
    // Ensure that is shaderstate is active current active shaderstate in shader gets updated address.
    if (shader.currently_active_state == &other)
    {
        shader.currently_active_state = this;
    }
}



ShaderState::~ShaderState()
{
    if (has_moved)
    {
        glDeleteVertexArrays(1, &vao_handle);
    }
}



void ShaderState::activate()
{
    if (!shader.is_active())
    {
        shader.activate();
    }
    if (shader.currently_active_state != this)
    {
        shader.currently_active_state = this;

        for (auto& u : uniforms)
        {
            u.second.upload();
        }

        glBindVertexArray(vao_handle);
    }
}



bool ShaderState::is_active() const
{
    return shader.is_active() && shader.currently_active_state == this;
}



const Shader& ShaderState::get_shader() const
{
    return shader;
}
