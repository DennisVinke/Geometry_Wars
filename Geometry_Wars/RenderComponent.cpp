#include "RenderComponent.h"
#include "MovementComponent.h"
#include "EntityManager.h"

RenderComponent::RenderComponent(Renderer& render):Component(),renderer(render), shape({ {-10, -10}, { -10, 10 }, { 10, 10}, { 10, -10} }) {}

RenderComponent::~RenderComponent(){}

void RenderComponent::execute() {
	shape.reset_transformation();
	shape.translate(getLocation());
	renderer.queueToRender(this);
}
void RenderComponent::init() {
}

void RenderComponent::render() {
	shape.render();
}

glm::vec2 RenderComponent::getLocation() {
	if (entity->hasComponent<MovementComponent>()) {
		return entity->getComponent<MovementComponent>()->getLocation();
	}
	else {
		return glm::vec2(0, 0);
	}
}

void RenderComponent::print() {
	std::cout << "RenderComponent!" << std::endl;
}

void RenderComponent::setColor(int r, int g, int b, int a) {
	shape.set_color(r, g, b, a);
}