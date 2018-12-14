#pragma once

#include <bitset>
#include <array>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <typeinfo>
//#include "Component.h"

class Component;
//Deze moeten allemaal een keer naar een constants class
constexpr auto maxComponents = 100; ;

using EntityID = std::size_t;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array <Component *, maxComponents >;

//Array[Components] for indexation
//Vector<Components> for update
//Dubbele component managements, maar moet wel want anders is het allemaal kut
//Sterker nog 3 dubbelle check want ook bitset

class Entity
{
private:
	EntityID id;
	ComponentBitSet containsComponents;
	ComponentArray componentArray;
	bool changedComponentFlag;
	std::vector<std::unique_ptr<Component>> componentList;
	bool alive = true;

public:
	Entity() = delete;
	Entity(EntityID i);

	void update();
	void draw();
	virtual ~Entity();

	void setComponentFlag(Component *);

	template<typename T, typename... Args>
	void setComponent(Args&&... values) {
		static_assert(std::is_base_of<Component, T>::value);
		T * component = new T(std::forward<Args>(values)...);
		component->entity = this;
		auto componentID = EntityManager::template getLastComponentID<T>();
		component->id = componentID;
		componentArray[componentID] = component;
		containsComponents[componentID] = true;
		std::unique_ptr<Component> uniqueComponent(component);
		componentList.emplace_back(std::move(uniqueComponent));
		std::cout << "De id in de manager: " << EntityManager::template getLastComponentID<T>() << std::endl;
		component->print();
	}

	//TODO: DENNIS DOE FIX
	template<typename T>
	T * getComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		auto componentID = EntityManager::template getLastComponentID<T>();
		T * component = static_cast<T*>(componentArray[componentID]);
		return component;
	}

	template<typename T>
	bool hasComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		auto componentID = EntityManager::template getLastComponentID<T>();
		return containsComponents[componentID];
	}


	//willen we components recyclen of willen we gewoon vernietigen
	//Bij recyclen moeten we iets maken die kijkt of de components al gebruikt worden door iets, aka componentmanager :'(
	template<typename T>
	void removeComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		auto componentID = EntityManager::template getLastComponentID<T>();
		if (containsComponents[componentID]) {
			//containsComponents[componentID] = false;
			auto component = componentArray[componentID];
			component->remove = true;
			component->id = componentID;
			this->changedComponentFlag = true;
			std::cout << "Hello I have been removed!" << std::endl;
			//ComponentArray[componentID] = nullptr
			//auto index = std::find(componentList.begin(), componentList.end(), component);
			//componentList.at(index-componentList.begin()).swap(componentList.at(componentList.end()- componentList.begin()));
			//std::iter_swap(index, componentList.end()-1);
			//componentList.pop_back();
			//std::cout << "De component: " << component->toString() << " will be removed" << std::endl;
		}
	}
	
	/*
	*@Aart: Weet jij hoe je de type van een parent van een unique pointer kunt opvragen?
	* Anders blijf ik mijn kut oplossing gebruiken
	*/
	template<typename T>
	bool removeFlaggedComponent() {
		static_assert(std::is_base_of<Component, T>::value);
		auto componentID = EntityManager::template getLastComponentID<T>();
		containsComponents[componentID] = false;
	}

	void setChangedComponent();
	bool changedComponents();
	void cleanUp();
	bool isActive();

	//virtual const int GetStaticEntityID() const = 0;

	//inline const int GetEntityID() const { return this->id; }

	//inline const int GetEntityID() const { return this->id; }

};

