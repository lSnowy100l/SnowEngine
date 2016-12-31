#pragma once
#include <iostream>

class World
{
private:
	double _world_gravity;
public:
	World(double gravity);
	double getWorldGravity() { return this->_world_gravity; }
	~World();
};