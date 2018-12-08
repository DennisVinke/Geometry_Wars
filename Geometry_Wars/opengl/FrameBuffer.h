#pragma once

#include <glad/glad.h>

class Texture2D;


class FrameBuffer
{

public:

    FrameBuffer();

    FrameBuffer(const FrameBuffer&) = delete;

    FrameBuffer(FrameBuffer&& other);

    ~FrameBuffer();


    void attach(Texture2D& texture, GLenum attachment_point);


private:

    GLuint framebuffer_handle;

    bool has_moved = false;


};
