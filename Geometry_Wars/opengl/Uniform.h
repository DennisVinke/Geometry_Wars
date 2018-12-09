#pragma once

#include <string>
#include <cstring>
#include <type_traits>

#include "types.h"
#include "UniformDefinition.h"



class ShaderState;




/// class Unfirom: Represents an uniform variable in an OpenGL shader program.
/**
 * Uniform variable can be used to send data to OpenGL shaders that can be used
 * to change the rendering properties of these Shaders. The Uniform class uses
 * the assignment operator to set values in the shader.
 */
class Uniform
{
    friend class Shader;
    friend class ShaderState;

public:

    // only allow Uniform's construction with a UniformDefinition
    Uniform() = delete;

    // copying is ambiguous.
    Uniform(const Uniform& other) = delete;

    /// Move constructor of Uniform
    Uniform(Uniform&& other);

    /// Uniforms are instantiated given a UniformDefinition and a ShaderState pointer.
    Uniform(const UniformDefinition& definition);

    /// Destructor for Uniform.
    ~Uniform();

    /// The value of the Uniform can be changed using the assignment operator.
    /// This first stores the new value at data_pointer, and then uploads the 
    /// data to OpenGL.
    template<typename T>
    void operator=(const T& value);


    const UniformDefinition& definition;


private:
    

    void upload();


    union DataComponent
    {
        float f_value;
        int32_t i_value;
        uint32_t u_value;
    };

    DataComponent * data_pointer;

};




template<typename T>
void Uniform::operator=(const T& value)
{
    if constexpr (std::is_fundamental<T>::value)
    {
        switch (base_type(definition.type))
        {
        case Type::FLOAT:
            data_pointer->f_value = static_cast<float>(value);
            break;
        case Type::INT:
            data_pointer->i_value = static_cast<int32_t>(value);
            break;
        case Type::UINT:
            data_pointer->u_value = static_cast<uint32_t>(value);
            break;
        case Type::BOOL:
            data_pointer->i_value = static_cast<int32_t>(value);
            break;
        }
    }
    else if constexpr (gl_type_info<T>::is_matrix)
    {
        assert(num_components(definition.type) == gl_type_info<T>::num_components);

        std::memcpy(data_pointer, &value, sizeof(T));
    }
    else
    {
        assert(num_components(definition.type) == gl_type_info<T>::num_components);

        switch (base_type(definition.type))
        {
        case Type::FLOAT:
            for (int i = 0; i < gl_type_info<T>::num_components; ++i)
                data_pointer[i].f_value = value[i];
            break;
        case Type::INT:
            for (int i = 0; i < gl_type_info<T>::num_components; ++i)
                data_pointer[i].i_value = value[i];
            break;
        case Type::UINT:
            for (int i = 0; i < gl_type_info<T>::num_components; ++i)
                data_pointer[i].u_value = value[i];
            break;
        case Type::BOOL:
            for (int i = 0; i < gl_type_info<T>::num_components; ++i)
                data_pointer[i].i_value = value[i];
            break;
        }
    }

    upload();
}
