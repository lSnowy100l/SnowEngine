#include "World.h"

World::World(double gravity) : _world_gravity(gravity) {
}

void World::update(GLfloat delta_time) {
	for (Entity* e : _entity_list) {
		if(e->isAffectedByGravity()) e->applyForce(Vec3GLf(0, -_world_gravity, 0));
		e->applyFrictionForce();
		e->updateMovement(delta_time);
	}
}

World::~World()
{
}
