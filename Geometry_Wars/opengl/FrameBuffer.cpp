#include "FrameBuffer.h"
#include "Texture.h"

#include <iostream>



FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
    : fbo_width(width), fbo_height(height)
{
    glGenFramebuffers(1, &framebuffer_handle);
}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
{
    framebuffer_handle = other.framebuffer_handle;
    other.cleanup_responsible = false;
}



FrameBuffer::~FrameBuffer()
{
    if (cleanup_responsible)
    {
        glDeleteFramebuffers(1, &framebuffer_handle);
    }
}



void FrameBuffer::add_texture(Texture::Type texture_type, GLenum pixel_format, GLenum attachment_point)
{
    attachments.emplace_back(Texture(texture_type, pixel_format), attachment_point);
    auto& tex = attachments.back().first;

    tex.bind();
    tex.set_size(fbo_width, fbo_height);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_handle);
    glFramebufferTexture(GL_FRAMEBUFFER, attachment_point, tex.get_handle(), 0);
    glViewport(0, 0, 640, 480);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void FrameBuffer::print_status()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_handle);
    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch (status)
    {
    case GL_FRAMEBUFFER_COMPLETE:
        std::cout << "GL_FRAMEBUFFER_COMPLETE\n";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n";
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        std::cout << "GL_FRAMEBUFFER_UNSUPPORTED\n";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        std::cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS\n";
        break;
    }    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void FrameBuffer::set_size(unsigned int width, unsigned int height)
{
    start_rendering();

    fbo_width = width;
    fbo_height = height;

    for (auto& [tex, a] : attachments)
    {
        tex.set_size(width, height);
    }
    glViewport(0, 0, width, height);

    stop_rendering();
}



unsigned int FrameBuffer::get_width()
{
    return fbo_width;
}


unsigned int FrameBuffer::get_height()
{
    return fbo_height;
}



void FrameBuffer::start_rendering()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_handle);
}


void FrameBuffer::stop_rendering()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


GLuint FrameBuffer::get_handle()
{
    return framebuffer_handle;
}


void FrameBuffer::bind_to(GLenum target)
{
    glBindFramebuffer(target, framebuffer_handle);
}


Texture& FrameBuffer::get_texture(int index)
{
    return attachments[index].first;
}