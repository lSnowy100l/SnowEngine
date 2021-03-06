#pragma once

#include <iostream>

#include "Utils.h"

#define CAM_SPEED_NORM 15
#define CAM_SPEED_FAST 50
#define JUMP_FORCE 30

class Camera
{
private:
	Vec3GLf _position = Vec3GLf();
	Mat4GLf _projectionMatrix;
	bool _use_abs_movement; //For alternating between jetpack movement
	bool _on_jump, _start_jump;
	GLfloat _yawRad, _pitchRad; //Avoid restacking continuosly
	Vec3GLf _iteration_increment; //Absolute positional increment for the next iteration
	GLfloat current_speed = CAM_SPEED_NORM; //Speed for camera and player movement
	GLfloat _pitch = 0, _yaw = 0;
public:
	Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar, Vec3GLf position);
	inline Vec3GLf getPosition() { return _position; }											// Returns actual camera position
	Vec3GLf getLookAt();																		// Returns actual camera view vector
	inline Mat4GLf getTranslationMatrix() { return Mat4GLf::translationMatrix(-_position); }	// Creates a translation matrix from camera's actual position
	Mat4GLf getRotationMatrix();
	void moveCamera(Vec3GLf increment);
	inline Mat4GLf getProjectionMatrix() { return _projectionMatrix; }							// Returns actual projection matrix
	inline void incAbsPos(Vec3GLf increment) { _position += increment; }						// Increments camera's position by @increment
	void absoluteMovement(Vec3GLf increment);
	void relativeMovement(Vec3GLf increment);
	void setMovementMode(bool mode);
	inline void setJump(bool jump) { this->_on_jump = jump; }
	inline void setStartJump(bool start_jump) { this->_start_jump = start_jump; }
	inline bool getStartJump() { return this->_start_jump; }
	inline bool getJump() { return this->_on_jump; }
	void storeNextIterationMove(GLfloat x, GLfloat y, GLfloat z);
	void updateMovementCamera(GLfloat delta_time, Vec3GLf * acceleration);
	void resetIterationMove() { _iteration_increment.x = 0; _iteration_increment.y = 0; _iteration_increment.z = 0; }
	GLfloat getCurrentSpeed() { return this->current_speed; }
	void setCurrentSpeed(GLfloat speed) { this->current_speed = speed; }
	inline void incPitch(GLfloat pitch) { _pitch += pitch; if (_pitch > 90) _pitch = 90; if (_pitch < -90) _pitch = -90; }
	inline void incYaw(GLfloat yaw) { _yaw += yaw; while (_yaw > 360) _yaw -= 360; while (_yaw < 0) _yaw += 360; }
	GLfloat getPitch() { return _pitch; }
	GLfloat getYaw() { return _yaw; }
	inline void setPosition(Vec3GLf pos) { _position.x = pos.x; _position.y = pos.y; _position.z = pos.z; }
	~Camera();
};

