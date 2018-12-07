#pragma once

#include <cstdint>

#include <glm/glm.hpp>


#include "opengl/types.h"



GL_REGISTER_DATA_TYPE(glm::vec2, float, false);
GL_REGISTER_DATA_TYPE(glm::vec3, float, false);
GL_REGISTER_DATA_TYPE(glm::vec4, float, false);

GL_REGISTER_DATA_TYPE(glm::ivec2, int32_t, false);
GL_REGISTER_DATA_TYPE(glm::ivec3, int32_t, false);
GL_REGISTER_DATA_TYPE(glm::ivec4, int32_t, false);

GL_REGISTER_DATA_TYPE(glm::uvec2, uint32_t, false);
GL_REGISTER_DATA_TYPE(glm::uvec3, uint32_t, false);
GL_REGISTER_DATA_TYPE(glm::uvec4, uint32_t, false);

GL_REGISTER_DATA_TYPE(glm::bvec2, bool, false);
GL_REGISTER_DATA_TYPE(glm::bvec3, bool, false);
GL_REGISTER_DATA_TYPE(glm::bvec4, bool, false);

GL_REGISTER_DATA_TYPE(glm::mat2,   float, true);
GL_REGISTER_DATA_TYPE(glm::mat2x3, float, true);
GL_REGISTER_DATA_TYPE(glm::mat2x4, float, true);

GL_REGISTER_DATA_TYPE(glm::mat3x2, float, true);
GL_REGISTER_DATA_TYPE(glm::mat3,   float, true);
GL_REGISTER_DATA_TYPE(glm::mat3x4, float, true);

GL_REGISTER_DATA_TYPE(glm::mat4x2, float, true);
GL_REGISTER_DATA_TYPE(glm::mat4x3, float, true);
GL_REGISTER_DATA_TYPE(glm::mat4,   float, true);

