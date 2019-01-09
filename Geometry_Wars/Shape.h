#pragma once


#include <glm/glm.hpp>

#include <vector>
#include <memory>


class ShaderState;



/// class Shape: represents a Shape that can be drawn using OpenGL.
/* 
 *  Shape class is the basis for simple polygon drawing on the graphics card
 *  Rendering of most Renderable game objects will be implemented using this class.
 *  It is important to only instantiate this class when the OpenGL context has been 
 *  properly initialized.
 */
class Shape
{

public:

    /// Default constructor.
    /*
     *  When using this constructor the shape will be initialized without any vertex
     *  data. This means the set_shape() function will still need to be called if, the 
     *  shape wants to show up when rendering. Transformation matrix is initialized to
     *  the identity matrix.
     */
    Shape();


    /// Shape constructor.
    /*
     *  When using this constructor the shape will be initialized with its shape
     *  The shape can still be changed using set_shape() function.
     *  Transformation matrix is initialized to the identity matrix.
     */
    Shape(const std::vector<glm::vec2>& shape);


    /// set_shape().
    /*
     *  Sets the vertex data of the shape. The vertices are relative to the shape's 
     *  transformation matrix's origin.
     */
    void set_shape(const std::vector<glm::vec2>& shape);


    /// get_shape().
    /*
     *  Returns the shape specified in the constructor or with the set_shape function.
     */
    const std::vector<glm::vec2>& get_shape() const;
    

    /// translate().
    /*
     *  Adds a translation to the transformation matrix.
     *  Note. This does not actually change the vertex data. Only renders it elsewhere.
     */
    void translate(glm::vec2 translation);


    /// translate().
    /*
     *  Adds a translation to the transformation matrix.
     *  Note. This does not actually change the vertex data. Only renders it elsewhere.
     */
    void translate(float x, float y);

    
    /// rotate(float angle_rads).
    /*
     *  Adds a rotation in radians to the transformation matrix.
     *  Note. This does not actually change the vertex data. Only renders it differently.
     */
    void rotate(float angle_rads);


    /// scale(glm::vec2 scale).
    /*
     *  Adds a scale to the transformation matrix.
     *  Note. This does not actually change the vertex data. Only renders it differently.
     */
    void scale(glm::vec2 scale);


    /// scale(float scale_x, float scale_y).
    /*
     *  Adds a scale to the transformation matrix.
     *  Note. This does not actually change the vertex data. Only renders it differently.
     */
    void scale(float scale_x, float scale_y);


    /// set_line_width(float width).
    /*
     *  Sets the linewidth opengl uses to draw the shape.
     */
    void set_line_width(float width);


    /// get_line_width().
    /*
     *  Gets the linewidth opengl uses to draw the shape.
     */
    float get_line_width() const;


    /// set_color().
    /*
     *  Sets the color that is used for rendering.
     */
    void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);


    /// reset_transformation().
    /*
     *  The functions translate, rotate and scale, change the transformation matrix cumulatively.
     *  This function allows you to reset the matrix to the identity matrix.
     */
    void reset_transformation();


    /// render().
    /*
     *  Draws the shape to the current framebuffer, using the default shader. This function first 
     *  ensures the right shader is active, then sets all the necessary settings, and then renders
     *  the shape. 
     */
    void render();

	float getWidht();

	float getHeight();
private:

    std::unique_ptr<ShaderState> shader_state;

    std::vector<glm::vec2> shape;

    float line_width = 1.0f;
    
    glm::vec4 color{ 1, 1, 1, 1 };

    glm::mat3 transformation{ 1 };


};