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
	if (this->_chk_manager->getBlockAt((GLuint)position.x, (GLuint)position.y, (GLuint)position.z) != NULL) return true;
	return false;
}

void Entity::applyFrictionForce()
{
	//Horizontal friction
	//We are looking for the block below, so its the entity height MINUS ONE
	Vec3GLf block_position(_position.x, _position.y - (GLfloat)(this->getEntityHeight()+1), _position.z);
	
	if (isOccupied(block_position)) {
		GLfloat sliding_coef = this->_chk_manager->getSlidingCoefficient(block_position.x, block_position.y, block_position.z);
		//Rationale:
		//We are applying an inverse force to the movement in x and z multiplied by a sliding coefficient
		//So basically it is (-1)*sign(v.x)*slide_coef*v.x and the same for z
		applyForce(Vec3GLf((-1)*signOfValue(&_forces.x)*sliding_coef*_velocity.x,0, (-1)*signOfValue(&_forces.z)*sliding_coef*_velocity.z));
	}
}


Entity::~Entity()
{
}
