#pragma once

#include <vector>

#include <glad/glad.h>


#include "Texture.h"


/// Class FrameBuffer, OpenGL FrameBuffer Object
/*
 *  Class representing an OpenGL FrameBuffer Object,
 *  to Use this class as a render target, textures need to be attached first.
 *  For more info on FBO's see: https://www.khronos.org/opengl/wiki/Framebuffer_Object
 */
class FrameBuffer
{

public:


    /// Constructor with width and height of the framebuffer.
    FrameBuffer(unsigned int width, unsigned int height);

    /// Copy constructor is deleted.
    FrameBuffer(const FrameBuffer&) = delete;

    /// Moving a FrameBuffer is allowed.
    FrameBuffer(FrameBuffer&& other);

    /// Destructor of FrameBuffer.
    ~FrameBuffer();


    /// Before being able to render to a FrameBuffer it first needs textures.
    void add_texture(Texture::Type texture_type, GLenum pixel_format, GLenum attachment_point);


    /// Resize the allocated textures with this function.
    void set_size(unsigned int width, unsigned int height);

    /// return the allocated width and height.
    unsigned int get_width();

    /// return the allocated width and height.
    unsigned int get_height();


    /// Queries OpenGL for the completeness state of this FBO and prints it to the console
    void print_status();


    /// Set this FrameBuffer as the current OpenGL rendering target.
    void start_rendering();


    /// Turn of rendering to the FrameBuffer, defaults back to no FrameBuffer.
    void stop_rendering();


    /// Wrapper for glBindFrameBuffer()
    void bind_to(GLenum target);


    /// Returns the internal handle of the OpenGL object.
    GLuint get_handle();


    /// Get a texture and sepcified index (Attachment index).
    Texture& get_texture(int index);


private:

    unsigned int fbo_width;
    unsigned int fbo_height;

    GLuint framebuffer_handle;

    bool cleanup_responsible = true;

    std::vector<std::pair<Texture, GLenum>> attachments;

};
