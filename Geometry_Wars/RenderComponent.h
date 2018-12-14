#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Shape.h"


//class MovementComponent;
class RenderComponent : public Component
{

private:


    Renderer& renderer;


public:
    Shape shape;


    RenderComponent()=delete;
	RenderComponent(Renderer&);

	~RenderComponent();

	void execute() override;
	void init() override;
	void print() override;

	void render();
	glm::vec2 getLocation();
};

