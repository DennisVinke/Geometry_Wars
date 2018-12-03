#pragma once

#include <bitset>
#include <array>
#include <algorithm>

constexpr auto maxComponents = 100; ;

using ComponentID = std::size_t;
using ComponentBitSet = std::bitset<maxComponents>;
//using ComponentArray = std::array<Component *, maxComponents>;

class Component;

class Entity
{
private: 
	 int id;
	 bool changedComponentFlag;

public:
	Entity();
	Entity(std::size_t i);
	
	void update();
	void draw();
	virtual ~Entity();

	void setComponentFlag(Component *);
	void addComponent(Component *);
	void removeComponent(Component *);
	
	void setChangedComponent();
	bool changedComponents();
	//virtual const int GetStaticEntityID() const = 0;

	inline const int GetEntityID() const { return this->id; }

};

