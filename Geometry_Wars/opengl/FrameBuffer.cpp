#include "FrameBuffer.h"
#include "Texture.h"




FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &framebuffer_handle);
}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
{
    framebuffer_handle = other.framebuffer_handle;
}



FrameBuffer::~FrameBuffer()
{
    if (has_moved)
    {
        glDeleteFramebuffers(1, &framebuffer_handle);
    }
}



void FrameBuffer::attach(Texture2D& texture, GLenum attachment_point)
{
    texture.bind();

    glFramebufferTexture(texture.texture_type, attachment_point, texture.get_handle(), 0);
}

