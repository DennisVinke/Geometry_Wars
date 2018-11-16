#pragma once

#include "DefaultRenderable.h"

#include <iostream>



class TestItem : public DefaultRenderable
{

    std::vector<glm::vec2> vertices =
    {
        glm::vec2(0, 0.5),
        glm::vec2(0.5, -0.5),
        glm::vec2(-0.5, -0.5)
    };

    std::vector<glm::u8vec4> colors =
    {
        { 100, 0, 200, 255 },
        { 255, 255, 0, 255 },
        { 255, 0, 255, 255 }
    };


public:

    TestItem()
        : DefaultRenderable(true)
    {
        set_vertex_data(vertices);
        set_colors(colors);
    }


    void render()
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

};
