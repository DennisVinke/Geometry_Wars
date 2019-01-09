#pragma once

#include <random>



namespace detail
{
    extern std::mt19937 random_engine;
}



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






#ifdef RANDOM_IMPLEMENTATION

namespace detail
{
    std::mt19937 random_engine;
}

#endif // RANDOM_IMPLEMENTATION
