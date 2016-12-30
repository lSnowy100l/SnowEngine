#include <iostream>
#include "Camera.h"
#include "common.h"

using namespace std;


Camera::Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar) : _projectionMatrix(Mat4GLf::projectionMatrix(width, height, fov, znear, zfar))
{
	_use_abs_movement = true;
}

Vec3GLf Camera::getLookAt() {
	return Vec3GLf::toVector(_pitch, _yaw);
}

Mat4GLf Camera::getRotationMatrix() {
#define DEG_TO_RAD 0.01745329251
	double radPitch = _pitch * DEG_TO_RAD, radYaw = _yaw * DEG_TO_RAD;
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

	incAbsPos(Vec3GLf(increment.x*cosf(_yawRad) - increment.z*sinf(_yawRad), increment.y, increment.z*cosf(_yawRad) + increment.x*sinf(_yawRad)));
}

void Camera::relativeMovement(Vec3GLf increment) {
	double absx, absy, absz;

	if (increment.x != 0) {
		absx = increment.x * cosf(_yawRad);
		absy = 0;
		absz = increment.x * sinf(_yawRad);
	}
	else if (increment.y != 0) {
		absx = 0;
		absy = increment.y;
		absz = 0;
	}
	else {
		absx = cosf(_pitchRad) * (- increment.z * sinf(_yawRad));
		absy = increment.z * sinf(_pitchRad);
		absz = cosf(_pitchRad) * increment.z * cosf(_yawRad);
		
	}
	
	incAbsPos(Vec3GLf(absx, absy, absz));
}

void Camera::setMovementMode(bool mode)
{
	this->_use_abs_movement = mode;
}


Camera::~Camera()
{
}
