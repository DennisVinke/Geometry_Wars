#pragma once

#include <random>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>



namespace detail
{
    static std::mt19937 random_engine;
}



class Transformation
{

public:

    Transformation() = default;

    void reset()
    {
        transformation = glm::mat3(1);
    }

    void translate(glm::vec2 translation)
    {
        transformation = glm::translate(transformation, translation);
    }

    void translate(float x, float y)
    {
        transformation = glm::translate(transformation, glm::vec2(x, y));
    }

    void rotate(float rotation)
    {
        transformation = glm::rotate(transformation, rotation);
    }

    void scale(glm::vec2 scale)
    {
        transformation = glm::scale(transformation, scale);
    }

    void scale(float x, float y)
    {
        transformation = glm::scale(transformation, glm::vec2(x, y));
    }

    glm::mat3 get()
    {
        return transformation;
    }

private:

    glm::mat3 transformation{ 1 };


};



inline float random(float min, float max)
{
    std::uniform_real_distribution<float> dist{ min, max };
    return dist(detail::random_engine);
}


inline float random(float max)
{
    return random(0.0f, max);
}


// Inclusive of both min and max
inline int random(int min, int max)
{
    std::uniform_int_distribution<int> dist{ min, max };
    return dist(detail::random_engine);
}


// Inclusive of max
inline int random(int max)
{
    return random(0, max);
}


