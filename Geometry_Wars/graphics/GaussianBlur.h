#pragma once

#include <memory>

#include "opengl/FrameBuffer.h"
#include "opengl/ShaderState.h"

class Texture;


/// class GaussianBlur
/**
 *  Gaussian blur filter that blurs an image from and FBO, and outputs a new FBO.
 *  The blur algorithm used uses multiple passes (horizontal and vertical), and
 *  multiple iterations of blurring for the most effective result. algorithm is based on:
 *  https://youtu.be/uZlwbWqQKpc
 */
class GaussianBlur
{

public:
    
    /// Constructor for GaussianBlur, arguments are width and height of the game screen,
    /// the relative size of the framebuffer for each consecutive pass of blurring,
    /// the amount of iterations of blurs (amount of passes).
    GaussianBlur(unsigned int w, unsigned int h, 
        float relative_size_per_iteration, unsigned int n_iterations);


    /// loads all the shaders that this class uses into the SHaderManager.
    static void load_shaders();


    /// When the window is resized every framebuffer needs to be reallocated.
    void window_resized(unsigned int w, unsigned int h);
    

    /// apply the blur effect onto a texture.
    FrameBuffer* apply(const Texture& texture);
    


private:

    std::vector<FrameBuffer> frame_buffers;

    float relative_size_per_iteration;
    
    unsigned int n_iterations;

    std::unique_ptr<ShaderState> vertical;
    std::unique_ptr<ShaderState> horizontal;


};
