#pragma once
#include "Vec3GLf.h"
#include "ChunkManager.h"
#include "common.h"

class Entity {
protected:
	Vec3GLf _forces = Vec3GLf(0, 0, 0);
	Vec3GLf _velocity = Vec3GLf(0, 0, 0);
	Vec3GLf _position;
	bool _in_air;
	bool _is_affected_by_gravity = true;
	GLfloat _movement_force;
	GLfloat _mass;

	ChunkManager * _chk_manager;
public:
	Entity(Vec3GLf position, GLfloat movement_force, GLfloat mass, ChunkManager * chk);
	bool isOccupied(Vec3GLf position);
	void applyFrictionForce();
	GLfloat getMass() { return _mass; }
	Vec3GLf getPosition() { return _position; }
	virtual bool isAffectedByGravity() = 0;
	inline void applyForce(Vec3GLf force) { _forces += force; }
	virtual void updateMovement(GLfloat delta_time) {}
	virtual GLfloat getEntityHeight() = 0;
	~Entity();
};

