#include "Shape.h"

#include "opengl/ShaderState.h"
#include "ShaderManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

#include "glm_type_registration.h"


Shape::Shape()
{
    shader_state = std::make_unique<ShaderState>(*ShaderManager::get("default"));
}



Shape::Shape(const std::vector<glm::vec2>& shape_)
{
    shader_state = std::make_unique<ShaderState>(*ShaderManager::get("default"));

    set_shape(shape_);
}

void Shape::set_shape(const std::vector<glm::vec2>& shape_)
{
    shape = shape_;
    shader_state->attribute["position"] = shape_;
}


const std::vector<glm::vec2>& Shape::get_shape() const
{
    return shape;
}


void Shape::translate(glm::vec2 translation)
{
    transformation = glm::translate(transformation, translation);
}

void Shape::translate(float x, float y)
{
    transformation = glm::translate(transformation, glm::vec2(x, y));
}


void Shape::rotate(float angle_rads)
{
    transformation = glm::rotate(transformation, angle_rads);
}


void Shape::scale(float scale_)
{
    scale(scale_, scale_);
}


void Shape::scale(glm::vec2 scale)
{
    transformation = glm::scale(transformation, scale);
}


void Shape::scale(float x, float y)
{
    transformation = glm::scale(transformation, glm::vec2(x, y));
}


void Shape::set_line_width(float width)
{
    line_width = width;
}



float Shape::get_line_width() const
{
    return line_width;
}


void Shape::set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    glm::vec4 c{ r, g, b, a };
    color = c / glm::vec4(255, 255, 255, 255);
}



void Shape::reset_transformation()
{
    transformation = glm::mat3(1);
}


void Shape::set_draw_mode(GLenum draw_mode_)
{
    draw_mode = draw_mode_;
}


void Shape::render()
{
    shader_state->activate();

    shader_state->uniform["color"] = color;
    shader_state->uniform["transformation"] = transformation;

    glLineWidth(line_width);
    glPointSize(line_width);
    //glPointSize(line_width / 2);

    glDrawArrays(draw_mode, 0, shape.size());
    //glDrawArrays(GL_POINTS, 0, shape.size());
}
