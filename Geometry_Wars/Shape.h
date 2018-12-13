#pragma once


#include <glm/glm.hpp>

#include <vector>
#include <memory>


class ShaderState;


class Shape
{

public:

    Shape();

    Shape(const std::vector<glm::vec2>& shape);


    void set_shape(const std::vector<glm::vec2>& shape);

    const std::vector<glm::vec2>& get_shape() const;
    

    void translate(glm::vec2 translation);

    void translate(float x, float y);

    
    void rotate(float angle_rads);


    void scale(glm::vec2 scale);

    void scale(float scale_x, float scale_y);



    void set_line_width(float width);

    float get_line_width() const;

    //void set_filled(bool fill);


    void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);


    void reset_transformation();


    void render();


private:

    std::unique_ptr<ShaderState> shader_state;

    std::vector<glm::vec2> shape;

    float line_width = 1.0f;
    
    glm::vec4 color{ 1, 1, 1, 1 };

    glm::mat3 transformation{ 1 };


};