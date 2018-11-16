#include "DefaultRenderable.h"

#include <iostream>



DefaultRenderable::DefaultRenderable(bool enable_multi_color, int z_order)
    : Renderable(z_order, Renderer::DEFAULT_SHADER), multi_color_enabled(enable_multi_color)
{
    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    glGenBuffers(1, &vertices_vbo_handle);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_handle);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    if (multi_color_enabled)
    {
        glGenBuffers(1, &colors_vbo_handle);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo_handle);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
        glEnableVertexAttribArray(1);
    }
}


DefaultRenderable::~DefaultRenderable()
{
    glDeleteVertexArrays(1, &vao_handle);
    glDeleteBuffers(1, &vertices_vbo_handle);

    if (multi_color_enabled)
    {
        glDeleteBuffers(1, &colors_vbo_handle);
    }
}


void DefaultRenderable::set_vertex_data(const std::vector<glm::vec2>& vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_handle);

    if (vertices_allocated < static_cast<int>(vertices.size()))
    {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_DYNAMIC_DRAW);
        vertices_allocated = vertices.size();
    }
    else
    {
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec2), vertices.data());
    }
}


void DefaultRenderable::set_colors(const std::vector<glm::u8vec4>& colors)
{
    if (multi_color_enabled)
    {
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo_handle);

        if (colors_allocated < static_cast<int>(colors.size()))
        {
            glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec2), colors.data(), GL_DYNAMIC_DRAW);
            colors_allocated = colors.size();
        }
        else
        {
            glBufferSubData(GL_ARRAY_BUFFER, 0, colors.size() * sizeof(glm::vec2), colors.data());
        }

        using_uniform_color = false;
    }
}


void DefaultRenderable::set_color(const glm::u8vec4& new_color)
{
    using_uniform_color = true;
    color = new_color;
}


void DefaultRenderable::bind()
{
    glBindVertexArray(vao_handle);

    //Renderer::DEFAULT_SHADER
    //Renderer::DEFAULT_SHADER

    //shader.set_uniform_1i("use_uniform_color", using_uniform_color);
    //shader.set_uniform_4f("uniform_color", color);
}
