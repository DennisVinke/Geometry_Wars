#pragma once


#include "NoCopy.h"
#include "NoMove.h"

#include "Renderer.h"




class Renderable : public NoCopy,
                   public NoMove
{

public:

    const int z_order;
    const ShaderID shader_id;


    Renderable(ShaderID id, int z)
        : shader_id(id), z_order(z)
    { }

    virtual ~Renderable() = default;

    virtual void bind() = 0;

    virtual void render() = 0;


};
