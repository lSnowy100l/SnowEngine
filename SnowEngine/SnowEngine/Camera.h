#pragma once

#include <iostream>

#include "Vec3GLf.h"
#include "Mat4GLf.h"

class Camera
{
private:
	
	Vec3GLf _position = Vec3GLf();
	Vec3GLf _realpos = Vec3GLf();
	Mat4GLf _projectionMatrix;
public:
	GLfloat _pitch = 0, _yaw = 0;
	Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar);
	inline Vec3GLf getPosition() { return _position; }											// Returns actual camera position
	Vec3GLf getLookAt();																		// Returns actual camera view vector
	inline Mat4GLf getTranslationMatrix() { return Mat4GLf::translationMatrix(-_position); }	// Creates a translation matrix from camera's actual position
	Mat4GLf getRotationMatrix();
	inline Mat4GLf getProjectionMatrix() { return _projectionMatrix; }							// Returns actual projection matrix
	inline void incAbsPos(Vec3GLf increment) { _position += increment; }						// Increments camera's position by @increment
	void incRelPos(Vec3GLf increment);
	inline void incPitch(GLfloat pitch) { _pitch += pitch; if (_pitch > 90) _pitch = 90; if (_pitch < -90) _pitch = -90; }
	inline void incYaw(GLfloat yaw) { _yaw += yaw; while (_yaw > 360) _yaw -= 360; while (_yaw < 0) _yaw += 360; }
	~Camera();
};

