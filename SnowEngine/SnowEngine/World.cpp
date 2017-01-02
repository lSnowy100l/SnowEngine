#include "World.h"

World::World(GLfloat gravity) :
	_world_gravity(gravity) {
}

void World::update(GLfloat delta_time) {
	for (Entity* e : _entity_list) {
		e->applyForce(Vec3GLf(0, -_world_gravity, 0));
		e->updateMovement(delta_time);
	}
}

World::~World()
{
}
