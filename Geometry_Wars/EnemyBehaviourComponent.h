#pragma once
#include "Component.h"
#include "MovementComponent.h"
#include "Shape.h"

struct EnemyBehaviour {
public:
	int bulletBehaviour = 0;
	int red, green, blue, alpha = 0;
	glm::vec2 speed = glm::vec2(0, 0);
	int size = 1;
	int cooldown;
	int speed;
	virtual void update() = 0;
};

struct Chaser:EnemyBehaviour {
	void update() override;
};

struct Random:EnemyBehaviour {
	void update() override;
};
struct ChaserWhenNear :EnemyBehaviour {
	void update() override;
};

struct Shooting :EnemyBehaviour {
	void update() override;
};

class EnemyBehaviourComponent: public Component{
public:
	EnemyBehaviourComponent(EnemyBehaviour *);
	~EnemyBehaviourComponent();
	void execute() override;
	void init() override;
	void print() override;
	void set_player_position(MovementComponent *);
private:
	MovementComponent * player_position;
	EnemyBehaviour * behaviour;
};
