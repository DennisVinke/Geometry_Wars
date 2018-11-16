#include "Renderer.h"
#include "Renderable.h"

#include "load_file_to_string.h"


Renderer::Renderer()
{
    shaders[DEFAULT_SHADER].add_stage(load_file_to_string("shaders/default.vert"), GL_VERTEX_SHADER);
    shaders[DEFAULT_SHADER].add_stage(load_file_to_string("shaders/default.frag"), GL_FRAGMENT_SHADER);
    shaders[DEFAULT_SHADER].compile();
}


void Renderer::render(Renderable& renderable)
{
    shaders[DEFAULT_SHADER].start();
    renderable.bind();
    renderable.render();

    int a = 9;
    int b = 10;

    int& c = a;

    c = b;
}