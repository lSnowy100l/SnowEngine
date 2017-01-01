#pragma once
#include <iostream>
#include <vector>

#include "Entity.h"

class World
{
private:
	double _world_gravity;
	std::vector<Entity*> _entity_list;
public:
	World(double gravity);
	void update(GLfloat delta_time);
	double getWorldGravity() { return this->_world_gravity; }
	inline void addEntity(Entity* entity) { _entity_list.push_back(entity); }
	~World();
};