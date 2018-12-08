#pragma once

#include "glad/glad.h"




class Texture2D
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


    struct Settings
    {
        Type type = Type::NORMALIZED_MIPMAP;
        GLenum pixel_format = GL_RGBA8;

        GLenum magnify_filter = GL_NEAREST;  // GL_NEAREST or GL_LINEAR, mipmapping filters are only supported on minify.
        GLenum minify_filter = GL_NEAREST;  // also allowed: GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST etc.

        GLenum texture_wrap_x = GL_REPEAT;
        GLenum texture_wrap_y = GL_REPEAT;
    };


    Texture2D() = delete;

    Texture2D(const Settings& settings);

    Texture2D(const Texture2D&) = delete;

    Texture2D(Texture2D&& other);

    ~Texture2D();


    void bind();


    GLuint get_handle();


    void allocate_empty(unsigned int width, unsigned int height);
    
    void resize(unsigned int width, unsigned int height);


    const Settings settings;
    const GLenum texture_type;


private:


    static constexpr GLenum texture_type_of(const Type& type);

    GLuint texture_handle;

    bool has_moved = false;


};
