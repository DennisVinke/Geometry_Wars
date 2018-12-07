#include <iostream>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "PlayerShip.h"

int main() {
	
	//stest
	std::cout << "Creating Entity manager" << std::endl;
	
	EntityManager * eManager = new EntityManager();
	ComponentManager * cManager = new ComponentManager();

	std::cout << "Creating Player Entity" << std::endl;

	GameObject * playerEntity = new PlayerShip(eManager->CreateEntity());
	
	//playerEntity->init();
	//cManager->createHealthComponent(playerEntity);

	int test;

	std::cin >> test;
	return 0;
}