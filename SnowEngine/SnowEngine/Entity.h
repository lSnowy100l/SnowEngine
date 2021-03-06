#pragma once
#include "Utils.h"

class Entity {
protected:
	Vec3GLf _forces	=	Vec3GLf(0, 0, 0);
	Vec3GLf _velocity =	Vec3GLf(0, 0, 0);
	Vec3GLf _position;

	bool _in_air;

	GLfloat _movement_force;
	GLfloat _mass;
public:
	// Constructor
	Entity(Vec3GLf position, GLfloat movement_force, GLfloat mass);
	inline GLfloat getMass() { return _mass; }
	inline Vec3GLf getPosition() { return _position; }
	inline void applyForce(Vec3GLf force) { _forces += force; }
	void updateMovement(GLfloat delta_time);
	inline virtual void additionalMovementUpdates() = 0;
	// Destructor
	~Entity();
};

