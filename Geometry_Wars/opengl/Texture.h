#pragma once

#include <utility>

#include "glad/glad.h"




// All Query functions both update the data stored client side, and return it.
// When you do not use get_handle() to change the opengl state of the texture,
// It is never necessary to query the state, from opengl, the state in this class
// is should always be up to date, if you only use it's member functions to change 
// the state


class Texture
{

public:

    enum class Type : GLsizei
    {
        MULTI_SAMPLED_2 = 2,
        MULTI_SAMPLED_4 = 4,
        MULTI_SAMPLED_8 = 8,
        MULTI_SAMPLED_16 = 16,
        NORMALIZED_MIPMAP = 17,
        NORMALIZED_NO_MIPMAP = 18,
        NON_NORMALIZED = 19
    };

    //=================================

    Texture() = delete;

    Texture(Type type, GLenum pixel_format);

    Texture(const Texture&) = delete;

    Texture(Texture&& other);

    ~Texture();

    //=================================

    void allocate_empty(unsigned int width, unsigned int height);

    void allocate_filled(unsigned int width, unsigned int height, const unsigned char* data);
    
    //=================================

    void set_size(unsigned int width, unsigned int height);

    std::pair<int, int> get_size() const;

    std::pair<int, int> query_size();

    int get_width() const;

    int get_height() const;

    int query_width();

    int query_height();
    
    //=================================

    void set_mag_filter(GLenum mag_filter);

    void set_min_filter(GLenum min_filter);

    GLenum get_mag_filter() const;

    GLenum get_min_filter() const;

    GLenum query_mag_filter();

    GLenum query_min_filter();

    //=================================
    
    void set_wrap_x(GLenum wrap_mode);

    void set_wrap_y(GLenum wrap_mode);

    GLenum get_wrap_x() const;

    GLenum get_wrap_y() const;

    GLenum query_wrap_x();

    GLenum query_wrap_y();

    //=================================

    int get_num_samples() const;

    int query_num_samples();

    //=================================

    void bind() const;

    GLuint get_handle() const;

    //=================================

    const GLenum binding_target;

    const GLenum pixel_format;

    const Type   type;


private:

    
    // Not const becuase OpenGL is not gauranteed to give the amount of samples asked for.
    int num_samples = 1;

    // Size is allowed to be changed dynamically.
    int texture_width = 0, texture_height = 0;

    // These properties are allowed to be changed dynamically.
    GLenum mag_filter, min_filter, texture_wrap_x, texture_wrap_y;


    GLuint texture_handle;

    bool cleanup_responsible = true;


    static constexpr GLenum binding_target_of(const Type& type);


};
