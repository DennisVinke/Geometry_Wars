#pragma once
#include <vector>
#include <stdio.h>
#include "Component.h"
#include <glm/glm.h>

class GameObject
{
public:
	GameObject();
	GameObject(std::vector<Component> * components, glm::Vec3 startingPosition);
	~GameObject();

private:
	std::vector<Component> componentList;

	glm::Vec3 position;

};

