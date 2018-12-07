#pragma once

#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>



constexpr uint32_t bin(
    uint8_t ordinal,
    uint8_t component_type,
    uint8_t num_components,
    uint8_t property_flags = 0u)
{
    // Adding property flags bits and shift.
    uint32_t representation = property_flags;
    representation <<= 8;

    // Adding number of components info and shift.
    representation |= num_components;
    representation <<= 8;

    // Adding number of components info and shift.
    representation |= component_type;
    representation <<= 8;

    // Finally add ordinal and return.
    return representation | ordinal;
}



struct BaseType
{
    static constexpr uint8_t F_32 = 0;
    static constexpr uint8_t F_64 = 1;
    static constexpr uint8_t U_8  = 2;
    static constexpr uint8_t U_16 = 3;
    static constexpr uint8_t U_32 = 4;
    static constexpr uint8_t U_64 = 5;
    static constexpr uint8_t I_8  = 6;
    static constexpr uint8_t I_16 = 7;
    static constexpr uint8_t I_32 = 8;
    static constexpr uint8_t B_8  = 9;
};



struct TypeFlags
{
    static constexpr uint8_t VALID_ATTRIBUTE = 0b00000001u;
    static constexpr uint8_t VALID_UNIFORM   = 0b00000010u;
    static constexpr uint8_t IS_FUNDAMENTAL  = 0b00000100u;
    static constexpr uint8_t IS_MATRIX       = 0b00001000u;
};



enum class Type : uint32_t
{
    FLOAT = bin(0,  BaseType::F_32, 1, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM | TypeFlags::IS_FUNDAMENTAL),
    VEC2  = bin(1,  BaseType::F_32, 2, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),
    VEC3  = bin(2,  BaseType::F_32, 3, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),
    VEC4  = bin(3,  BaseType::F_32, 4, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),

    INT   = bin(4,  BaseType::I_32, 1, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM | TypeFlags::IS_FUNDAMENTAL),
    IVEC2 = bin(5,  BaseType::I_32, 2, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),
    IVEC3 = bin(6,  BaseType::I_32, 3, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),
    IVEC4 = bin(7,  BaseType::I_32, 4, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),

    UINT  = bin(8,  BaseType::U_32, 1, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM | TypeFlags::IS_FUNDAMENTAL),
    UVEC2 = bin(9,  BaseType::U_32, 2, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),
    UVEC3 = bin(10, BaseType::U_32, 3, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),
    UVEC4 = bin(11, BaseType::U_32, 4, TypeFlags::VALID_ATTRIBUTE | TypeFlags::VALID_UNIFORM),

    BOOL  = bin(12, BaseType::B_8, 1, TypeFlags::VALID_UNIFORM | TypeFlags::IS_FUNDAMENTAL),
    BVEC2 = bin(13, BaseType::B_8, 2, TypeFlags::VALID_UNIFORM),
    BVEC3 = bin(14, BaseType::B_8, 3, TypeFlags::VALID_UNIFORM),
    BVEC4 = bin(15, BaseType::B_8, 4, TypeFlags::VALID_UNIFORM),

    MAT_2x2 = bin(16, BaseType::F_32, 4,  TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),
    MAT_2x3 = bin(17, BaseType::F_32, 6,  TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),
    MAT_2x4 = bin(18, BaseType::F_32, 8,  TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),

    MAT_3x2 = bin(19, BaseType::F_32, 6,  TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),
    MAT_3x3 = bin(20, BaseType::F_32, 9,  TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),
    MAT_3x4 = bin(21, BaseType::F_32, 12, TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),

    MAT_4x2 = bin(22, BaseType::F_32, 8,  TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),
    MAT_4x3 = bin(23, BaseType::F_32, 12, TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX),
    MAT_4x4 = bin(24, BaseType::F_32, 16, TypeFlags::VALID_UNIFORM | TypeFlags::IS_MATRIX)
};




constexpr uint32_t num_components(const Type& t)
{
    return (static_cast<uint32_t>(t) & 0x00ff0000u) >> 16;
}




constexpr GLenum gl_base_type(const Type& t)
{
    if (t == Type::FLOAT || t == Type::VEC2 || t == Type::VEC3 || t == Type::VEC4)
    {
        return GL_FLOAT;
    }
    else if (t == Type::INT || t == Type::IVEC2 || t == Type::IVEC3 || t == Type::IVEC4)
    {
        return GL_INT;
    }
    else if (t == Type::UINT || t == Type::UVEC2 || t == Type::UVEC3 || t == Type::UVEC4)
    {
        return GL_UNSIGNED_INT;
    }
    else if (t == Type::BOOL || t == Type::BVEC2 || t == Type::BVEC3 || t == Type::BVEC4)
    {
        return GL_BOOL;
    }
    else
    {
        return 0;
    }
}



constexpr Type base_type(const Type& t)
{
    if (t == Type::FLOAT || t == Type::VEC2 || t == Type::VEC3 || t == Type::VEC4)
    {
        return Type::FLOAT;
    }
    else if (t == Type::INT || t == Type::IVEC2 || t == Type::IVEC3 || t == Type::IVEC4)
    {
        return Type::INT;
    }
    else if (t == Type::UINT || t == Type::UVEC2 || t == Type::UVEC3 || t == Type::UVEC4)
    {
        return Type::UINT;
    }
    else if (t == Type::BOOL || t == Type::BVEC2 || t == Type::BVEC3 || t == Type::BVEC4)
    {
        return Type::BOOL;
    }
    else
    {
        return Type::FLOAT;
    }
}


