#include "Texture.h"

#include <cassert>






Texture::Texture(Type type_, GLenum pixel_format_)
    : binding_target(binding_target_of(type_)), pixel_format(pixel_format_), type(type_)
{
    glGenTextures(1, &texture_handle);
    glBindTexture(binding_target, texture_handle);

    set_wrap_x(GL_REPEAT);
    set_wrap_y(GL_REPEAT);

    if (type == Type::NORMALIZED_MIPMAP)
    {
        set_mag_filter(GL_LINEAR);
        set_min_filter(GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        set_mag_filter(GL_LINEAR);
        set_min_filter(GL_LINEAR);
    }
}




Texture::Texture(Texture&& other)
    : binding_target(other.binding_target), pixel_format(other.pixel_format), 
    type(other.type), texture_handle(other.texture_handle)
{
    other.cleanup_responsible = false;
}




Texture::~Texture()
{
    if (cleanup_responsible)
    {
        glDeleteTextures(1, &texture_handle);
    }
}




void Texture::allocate_empty(unsigned int width, unsigned int height)
{
    set_size(width, height);
}


// void allocate_from(...)




void Texture::set_size(unsigned int width, unsigned int height)
{
    bind();

    if (binding_target == GL_TEXTURE_2D_MULTISAMPLE)
    {
        glTexImage2DMultisample(binding_target, static_cast<GLsizei>(type),
            pixel_format, width, height, GL_TRUE);

        query_num_samples();  // Updates member num_samples
    }
    else
    {
        glTexImage2D(binding_target, 0, pixel_format, width, height,
            0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        if (type == Type::NORMALIZED_MIPMAP)
        {
            glGenerateMipmap(binding_target);
        }
    }

    texture_width = width;
    texture_height = height;
}



std::pair<int, int> Texture::get_size() const
{
    return { texture_width, texture_height };
}

std::pair<int, int> Texture::query_size()
{
    bind();
    glGetTexLevelParameteriv(binding_target, 0, GL_TEXTURE_WIDTH, &texture_width);
    glGetTexLevelParameteriv(binding_target, 0, GL_TEXTURE_HEIGHT, &texture_height);
    return { texture_width, texture_height };
}

int Texture::get_width() const
{
    return texture_width;
}

int Texture::get_height() const
{
    return texture_height;
}

int Texture::query_width()
{
    bind();
    glGetTexLevelParameteriv(binding_target, 0, GL_TEXTURE_WIDTH, &texture_width);
    return texture_width;
}

int Texture::query_height()
{
    bind();
    glGetTexLevelParameteriv(binding_target, 0, GL_TEXTURE_HEIGHT, &texture_height);
    return texture_height;
}



void Texture::set_mag_filter(GLenum filter)
{
    bind();
    glTexParameteri(binding_target, GL_TEXTURE_MAG_FILTER, filter);
    mag_filter = filter;
}

void Texture::set_min_filter(GLenum filter)
{
    bind();
    glTexParameteri(binding_target, GL_TEXTURE_MIN_FILTER, filter);
    min_filter = filter;
}

GLenum Texture::get_mag_filter() const
{
    return mag_filter;
}

GLenum Texture::get_min_filter() const
{
    return min_filter;
}

GLenum Texture::query_mag_filter()
{
    bind();
    glTexParameterIuiv(binding_target, GL_TEXTURE_MAG_FILTER, &mag_filter);
    return mag_filter;
}

GLenum Texture::query_min_filter()
{
    bind();
    glTexParameterIuiv(binding_target, GL_TEXTURE_MIN_FILTER, &min_filter);
    return min_filter;
}


void Texture::set_wrap_x(GLenum wrap_mode)
{
    bind();
    glTexParameteri(binding_target, GL_TEXTURE_WRAP_S, wrap_mode);
    texture_wrap_x = wrap_mode;
}

void Texture::set_wrap_y(GLenum wrap_mode)
{
    bind();
    glTexParameteri(binding_target, GL_TEXTURE_WRAP_T, wrap_mode);
    texture_wrap_y = wrap_mode;
}

GLenum Texture::get_wrap_x() const
{
    return texture_wrap_x;
}

GLenum Texture::get_wrap_y() const
{
    return texture_wrap_y;
}

GLenum Texture::query_wrap_x()
{
    bind();
    glTexParameterIuiv(binding_target, GL_TEXTURE_WRAP_S, &texture_wrap_x);
    return texture_wrap_x;
}

GLenum Texture::query_wrap_y()
{
    bind();
    glTexParameterIuiv(binding_target, GL_TEXTURE_WRAP_T, &texture_wrap_y);
    return texture_wrap_y;
}



int Texture::get_num_samples() const
{
    return num_samples;
}



int Texture::query_num_samples()
{
    glGetTexLevelParameteriv(binding_target, 0, GL_TEXTURE_SAMPLES, &num_samples);
    return num_samples;
}


void Texture::bind() const
{
    glBindTexture(binding_target, texture_handle);
}




GLuint Texture::get_handle() const
{
    return texture_handle;
}






constexpr GLenum Texture::binding_target_of(const Type& type)
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

