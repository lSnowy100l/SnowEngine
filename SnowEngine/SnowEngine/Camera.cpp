#include <iostream>
#include "Camera.h"

using namespace std;


Camera::Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar, Vec3GLf position) : _projectionMatrix(Mat4GLf::projectionMatrix(width, height, fov, znear, zfar))
{
	this->_position = position;
	_use_abs_movement = true;
	_on_jump = false;
	_start_jump = false;
}

Vec3GLf Camera::getLookAt() {
	return Vec3GLf::toVector(_pitch, _yaw);
}

Mat4GLf Camera::getRotationMatrix() {
	float radPitch = _pitch * DEG_TO_RAD, radYaw = _yaw * DEG_TO_RAD;
	Vec3GLf right_v	(cosf(radYaw), 0, sinf(radYaw));
	Vec3GLf up_v	(sinf(radYaw)*sinf(radPitch), cosf(radPitch), -cosf(radYaw)*sinf(radPitch));
	Vec3GLf back_v	(-sinf(radYaw)*cosf(radPitch), sinf(radPitch), cosf(radYaw)*cosf(radPitch));
	
	Mat4GLf rotationMatrix = Mat4GLf::viewRotationMatrix(right_v, back_v, up_v);

	return rotationMatrix;
}

void Camera::moveCamera(Vec3GLf increment) {
	this->_yawRad = _yaw*DEG_TO_RAD;
	this->_pitchRad = _pitch*DEG_TO_RAD;
	if (this->_use_abs_movement) absoluteMovement(increment); else relativeMovement(increment);
}

void Camera::absoluteMovement(Vec3GLf increment) {

	//incAbsPos(Vec3GLf(increment.x*cosf(_yawRad) - increment.z*sinf(_yawRad), increment.y, increment.z*cosf(_yawRad) + increment.x*sinf(_yawRad)));
	storeNextIterationMove(increment.x*cosf(_yawRad) - increment.z*sinf(_yawRad), increment.y, increment.z*cosf(_yawRad) + increment.x*sinf(_yawRad));
}

void Camera::relativeMovement(Vec3GLf increment) {
	GLfloat absx = 0, absy = 0, absz = 0;

	//if (increment.x != 0) {
		absx += increment.x * cosf(_yawRad);
		//absy += 0;
		absz += increment.x * sinf(_yawRad);
	//}
	//else if (increment.y != 0) {
		//absx += 0;
		absy += increment.y;
		//absz += 0;
	//}
	//else {
		absx += /*cosf(_pitchRad) */ (-increment.z * sinf(_yawRad));
		//absy += increment.z * sinf(_pitchRad);
		absz += /*cosf(_pitchRad) */ increment.z * cosf(_yawRad);
	//}
	
	//incAbsPos(Vec3GLf(absx, absy, absz));
	storeNextIterationMove(absx, absy, absz);
}

void Camera::setMovementMode(bool mode)
{
	this->_use_abs_movement = mode;
}

void Camera::storeNextIterationMove(GLfloat x, GLfloat y, GLfloat z)
{
	_iteration_increment.x += x; _iteration_increment.y += y; _iteration_increment.z += z;
}

void Camera::updateMovementCamera(GLfloat delta_time, Vec3GLf * acceleration) {
	GLfloat theoretical_speed = this->getCurrentSpeed()*delta_time;
	GLfloat jump_force = _iteration_increment.y;


	_iteration_increment = _iteration_increment.normalized();
	_iteration_increment *= theoretical_speed;

	
	if (this->_start_jump) { //If we jumped, do not normalize the jumping power
		acceleration->y += jump_force;
		this->_start_jump = false;
	}
  
	if (this->_use_abs_movement) { //Gravity should only affect if jetpack is off
		_iteration_increment.x += (acceleration->x * delta_time);
		_iteration_increment.y += (acceleration->y * delta_time);
		_iteration_increment.z += (acceleration->z * delta_time);
	}
	else {
		//Jetpack is on (do not accumulate gravitational force)
		acceleration->reset();
	}

	this->incAbsPos(this->_iteration_increment); 
	this->resetIterationMove();
}


Camera::~Camera()
{
}
