#include "Entity.h"

Entity::Entity(Vec3GLf position, GLfloat movementForce, GLfloat mass) :
	_position(position),
	_movement_force(movementForce),
	_mass(mass)
{
}

void Entity::updateMovement(GLfloat delta_time)
{
	_velocity += _forces / _mass;
	_position += _velocity * delta_time;

	additionalMovementUpdates();
	_forces.reset();
}

Entity::~Entity()
{
}
