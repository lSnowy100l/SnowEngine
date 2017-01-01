#include "Entity.h"



Entity::Entity(Vec3GLf position, GLfloat movementForce, GLfloat mass) :
	_position(position),
	_movement_force(movementForce),
	_mass(mass)
{
}


void Entity::updateMovement(GLfloat delta_time)
{
	_forces /= _mass;
	_velocity += _forces;
	_position.x += _velocity.x*delta_time;
	_position.y += _velocity.y*delta_time;
	_position.z += _velocity.z*delta_time;

	additionalMovementUpdates(delta_time);
	_forces.reset();
}

Entity::~Entity()
{
}
