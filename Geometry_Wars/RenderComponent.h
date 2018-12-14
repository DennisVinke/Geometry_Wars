#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Shape.h"

//class MovementComponent;
class RenderComponent :protected Component
{
	friend class Entity;
private:
	Shape shape;
	Renderer& renderer;
public:
	RenderComponent()=delete;
	RenderComponent(Renderer&);
	~RenderComponent();

	void execute() override;
	void init() override;
	void toString() override;

	void render();
	glm::vec2 getLocation();
};

