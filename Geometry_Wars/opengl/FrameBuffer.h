#pragma once

#include <vector>

#include <glad/glad.h>


#include "Texture.h"



class FrameBuffer
{

public:

    FrameBuffer(unsigned int width, unsigned int height);

    FrameBuffer(const FrameBuffer&) = delete;

    FrameBuffer(FrameBuffer&& other);

    ~FrameBuffer();


    void add_texture(Texture::Type texture_type, GLenum pixel_format, GLenum attachment_point);


    void set_size(unsigned int width, unsigned int height);

    unsigned int get_width();

    unsigned int get_height();



    void print_status();


    void start_rendering();


    void stop_rendering();


    void bind_to(GLenum target);


    GLuint get_handle();


    Texture& get_texture(int index);


private:

    unsigned int fbo_width;
    unsigned int fbo_height;

    GLuint framebuffer_handle;

    bool cleanup_responsible = true;

    std::vector<std::pair<Texture, GLenum>> attachments;

};
