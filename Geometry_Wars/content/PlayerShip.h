#pragma once
#include <list>
#include"engine/GameObject.h"

class PlayerShip : public GameObject
{

//Reference naar componentManager vs zelf bijhouden van componenten 
public:

	PlayerShip() = delete;

	PlayerShip(Entity& entity);

	//PlayerShip(unsigned int id, unsigned int components, std::list<Component *> componentReference);
	~PlayerShip();
	
	void init() override;

private:

};

