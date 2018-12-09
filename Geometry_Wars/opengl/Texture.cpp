#include "Texture.h"

#include <cassert>






Texture2D::Texture2D(const Settings& settings_)
    : texture_type(texture_type_of(settings_.type)), settings(settings_)
{
    glGenTextures(1, &texture_handle);

    glBindTexture(texture_type, texture_handle);

    // Maybe add some sort of correctness checking?
    // shoudl i set filters in general when using rectange texture?
    glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, settings.magnify_filter);
    glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, settings.minify_filter);

    glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, settings.texture_wrap_x);
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, settings.texture_wrap_y);
}




Texture2D::Texture2D(Texture2D&& other)
    : texture_type(other.texture_type), settings(other.settings)
{
    texture_handle = other.texture_handle;
    other.has_moved = true;
}




Texture2D::~Texture2D()
{
    // If the texture has been moved this instance is no longer responsible for cleanup.
    if (!has_moved)
    {
        glDeleteTextures(1, &texture_handle);
    }
}




void Texture2D::allocate_empty(unsigned int width, unsigned int height)
{
    assert(!has_moved);

    bind();

    if (texture_type == GL_TEXTURE_2D_MULTISAMPLE)
    {
        glTexImage2DMultisample(texture_type, static_cast<GLsizei>(settings.type), 
            settings.pixel_format, width, height, GL_TRUE); // TODO: fixed sample locations?
    }
    else
    {
        glTexImage2D(texture_type, 0, settings.pixel_format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        if (settings.type == Type::NORMALIZED_MIPMAP)
        {
            glGenerateMipmap(texture_type);
        }
    }
}



void Texture2D::resize(unsigned int width, unsigned int height)
{
    allocate_empty(width, height);
}



void Texture2D::bind()
{
    glBindTexture(texture_type, texture_handle);
}




GLuint Texture2D::get_handle() const
{
    return texture_handle;
}




constexpr GLenum Texture2D::texture_type_of(const Type& type)
{
    if (type == Type::NON_NORMALIZED)
    {
        return GL_TEXTURE_RECTANGLE;
    }
    else if (type == Type::NORMALIZED_MIPMAP || type == Type::NORMALIZED_NO_MIPMAP)
    {
        return GL_TEXTURE_2D;
    }
    else
    {
        return GL_TEXTURE_2D_MULTISAMPLE;
    }
}

