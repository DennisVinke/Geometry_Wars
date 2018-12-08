#include "FrameBuffer.h"
#include "Texture.h"




FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
    : fbo_width(width), fbo_height(height)
{
    glGenFramebuffers(1, &framebuffer_handle);
}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
{
    framebuffer_handle = other.framebuffer_handle;
    other.has_moved = true;
}



FrameBuffer::~FrameBuffer()
{
    if (has_moved)
    {
        glDeleteFramebuffers(1, &framebuffer_handle);
    }
}



void FrameBuffer::add_texture(const Texture2D::Settings& texture_settings, GLenum attachment_point)
{
    attachments.emplace_back(Texture2D(texture_settings), attachment_point);
    attachments.back().first.bind();
    attachments.back().first.resize(fbo_width, fbo_height);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_handle);
    glFramebufferTexture(attachments.back().first.texture_type, attachment_point, attachments.back().first.get_handle(), 0);
}



void FrameBuffer::resize(unsigned int width, unsigned int height)
{
    fbo_width = width;
    fbo_height = height;

    for (auto& [tex, a] : attachments)
    {
        tex.resize(width, height);
    }
}


void FrameBuffer::start_rendering()
{
    glBindFramebuffer(framebuffer_handle, GL_FRAMEBUFFER);
}


void FrameBuffer::stop_rendering()
{
    glBindFramebuffer(0, GL_FRAMEBUFFER);
}


GLuint FrameBuffer::get_handle()
{
    return framebuffer_handle;
}


void FrameBuffer::bind_to(GLenum target)
{
    glBindFramebuffer(framebuffer_handle, target);
}
