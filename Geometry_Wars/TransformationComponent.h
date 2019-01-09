#pragma once

#include "Component.h"

#include <string>

#include <glm/glm.hpp>


class TransformationComponent : public Component
{

public:

    void reset();

    void translate(float x, float y);

    void translate(glm::vec2 translation);

    void rotate(float rotation);

    void scale(float x, float y);

    void scale(glm::vec2 scale);


    glm::vec2 get_position();


    void execute() {}


    void init() {}


    void print() { }


private:

    glm::mat3 transformation{ 1 };


};