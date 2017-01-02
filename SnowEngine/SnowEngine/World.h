#pragma once

#include <iostream>
#include <vector>

#include "Entity.h"

class World
{
private:
	GLfloat _world_gravity;
	std::vector<Entity*> _entity_list;
public:
	World(GLfloat gravity);
	void update(GLfloat delta_time);
	inline GLfloat getWorldGravity() { return this->_world_gravity; }
	inline void addEntity(Entity* entity) { _entity_list.push_back(entity); }
	~World();
};