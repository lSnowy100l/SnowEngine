#include "Entity.h"



Entity::Entity(Vec3GLf position, GLfloat movementForce, GLfloat mass, ChunkManager * chk) :
	_position(position),
	_movement_force(movementForce),
	_mass(mass),
	_chk_manager(chk)
{
}

bool Entity::isOccupied(Vec3GLf position)
{
	if (this->_chk_manager->getBlockAt((unsigned)position.x, (unsigned)position.y, (unsigned)position.z) != NULL) return true;
	return false;
}

void Entity::applyFrictionForce()
{
	/*
	//Horizontal friction
	GLfloat ground_touch = _position.y - this->getEntityHeight();
	if (isOccupied(Vec3GLf(0, ground_touch, 0))) {

	}
	*/
}


Entity::~Entity()
{
}
