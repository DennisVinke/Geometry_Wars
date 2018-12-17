#include "TransformationComponent.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>




void TransformationComponent::reset()
{
    transformation = glm::mat3(1);
}


void TransformationComponent::translate(glm::vec2 translation)
{
    transformation = glm::translate(transformation, translation);
}

void TransformationComponent::translate(float x, float y)
{
    transformation = glm::translate(transformation, glm::vec2(x, y));
}


void TransformationComponent::rotate(float rotation)
{
    transformation = glm::rotate(transformation, rotation);
}


void TransformationComponent::scale(glm::vec2 scale)
{
    transformation = glm::scale(transformation, scale);
}


void TransformationComponent::scale(float x, float y)
{
    transformation = glm::scale(transformation, glm::vec2(x, y));
}



glm::vec2 TransformationComponent::get_position()
{
    return glm::vec2(transformation[2][0], transformation[2][1]);
}
