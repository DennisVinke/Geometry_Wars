#pragma once
#include "engine/Component.h"
#include "components/MovementComponent.h"
#include "graphics/Shape.h"

class EnemyBehaviour;
class EnemyBehaviourComponent: public Component{
public:
	EnemyBehaviourComponent(EnemyBehaviour *, Entity *);
	~EnemyBehaviourComponent();
	void execute() override;
	void init() override;
	void print() override;
	void set_player_position(MovementComponent *);
private:
	Entity * player;
	EnemyBehaviour * behaviour;
};
