#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <glad/glad.h>



void configure_context()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
}


void print_context_status()
{
    int profile, major_version, minor_version, double_buffering;
    int red_bits, green_bits, blue_bits, alpha_bits;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &double_buffering);
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red_bits);
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &green_bits);
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &blue_bits);
    SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &alpha_bits);

    std::cout << "version:\t" << major_version << "." << minor_version << "\n";
    std::cout << "core profile:\t" << ((profile == SDL_GL_CONTEXT_PROFILE_CORE) ? "true" : "false") << "\n";
    std::cout << "vsync:\t\t" << (double_buffering == 1 ? "true" : "false") << "\n";
    std::cout << "rgba bits:\t" << red_bits << ", " << green_bits << ", " << blue_bits << ", " << alpha_bits << "\n";
}

#include "glm_type_registration.h"

#include "Renderer.h"


int main(int argc, char* args[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Error initializing SDL";
        std::exit(1);
    }

    SDL_Window * window = nullptr;
    SDL_GLContext opengl_context = nullptr;

    window = SDL_CreateWindow("test", 100, 100, 640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


    configure_context();

    opengl_context = SDL_GL_CreateContext(window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_GL_SetSwapInterval(1);

    print_context_status();


    // * *************************************************

    //Application

    Renderer renderer;
    //DefaultShader default_shader;
    //default_shader.start();

    renderer.resized(640, 480);
    // * *************************************************


    for (bool quit = false; !quit;)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_WINDOWEVENT
                && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                renderer.resized(event.window.data1, event.window.data2);
                std::cout << "Window resized to: " << event.window.data1 << ", " << event.window.data2 << "\n";
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        renderer.render_frame();
        // * *************************************************


        // * *************************************************


        SDL_GL_SwapWindow(window);
    }


    SDL_DestroyWindow(window);


    SDL_Quit();

    return 0;
}
