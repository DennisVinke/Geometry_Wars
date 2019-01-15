#pragma once
#include "components/MovementComponent.h"
#include "graphics/Shape.h"

struct EnemyBehaviour 
{

public:

	int bulletBehaviour = 0;
	int red = 125;
	int green = 255;
	int blue = 255;
	int alpha = 255;
	glm::vec2 speed = glm::vec2(1, 1);
	int size = 10;
	int cooldown;
	float movement_speed;
	std::vector<glm::vec2> shape;
	virtual glm::vec2 update(Entity *, glm::vec2 player_position) = 0;
	MovementComponent * current_position;
	glm::vec2 player_position;
};

struct Chaser :EnemyBehaviour 
{
    Chaser()
    {
        red = 125;
        blue = 255;
        green = 255;
        alpha = 255;
        speed = glm::vec2(5, 5);
        shape = { {0, 20}, {20, 0}, {0, -20}, {-20, 0} };
    }

    glm::vec2 update(Entity *, glm::vec2 player_position) override;

};

struct Random :EnemyBehaviour 
{
    Random()
    {

    }

	glm::vec2 update(Entity *, glm::vec2 player_position) override;

};
struct ChaserWhenNear :EnemyBehaviour 
{
    ChaserWhenNear()
    {

    }

	int min_chase_distance = 100;

	glm::vec2 update(Entity *, glm::vec2 player_position) override;

};

struct Shooting : Chaser 
{
    Shooting()
    {

    }

	glm::vec2 shoot_speed =  glm::vec2(1, 1);
	glm::vec2 update(Entity *, glm::vec2 player_position);
	//inline glm::vec2 get_shoot_vector() {
	//	return shoot_vector*shoot_speed;
	//}
};