#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Shader.h"
#include "Renderable.h"



class DefaultRenderable : public Renderable
{

public:

    DefaultRenderable(bool enable_multi_color = false, int z_order = 0);

    virtual ~DefaultRenderable();

    virtual void render() = 0;

    virtual void bind();


protected:

    void set_vertex_data(const std::vector<glm::vec2>& vertices);

    void set_colors(const std::vector<glm::u8vec4>& colors);

    void set_color(const glm::u8vec4& color);


private:

    GLuint vao_handle;
    GLuint vertices_vbo_handle;
    GLuint colors_vbo_handle;

    const bool multi_color_enabled;
    bool using_uniform_color = true;

    int vertices_allocated = -1;
    int colors_allocated = -1;

    glm::u8vec4 color{ 255, 255, 255, 255 };

};



