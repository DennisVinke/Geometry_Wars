#pragma once

#include <memory>

#include "opengl/FrameBuffer.h"
#include "opengl/ShaderState.h"

class Texture;


class GaussianBlur
{


public:
    
    GaussianBlur(unsigned int w, unsigned int h, 
        float relative_size_per_iteration, unsigned int n_iterations);


    static void load_shaders();


    void window_resized(unsigned int w, unsigned int h);
    

    FrameBuffer* apply(const Texture& texture);
    
    
    FrameBuffer* debug(const Texture& texture);


private:

    std::vector<FrameBuffer> frame_buffers;

    float relative_size_per_iteration;
    
    unsigned int n_iterations;

    std::unique_ptr<ShaderState> vertical;
    std::unique_ptr<ShaderState> horizontal;


};