#include <iostream>
#include "Camera.h"
#include "common.h"

using namespace std;


Camera::Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar) : _projectionMatrix(Mat4GLf::projectionMatrix(width, height, fov, znear, zfar))
{
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

void Camera::incRelPos(Vec3GLf increment) {
	double yawRad = _yaw*DEG_TO_RAD;
	double pitchRad = _pitch*DEG_TO_RAD;

	double advance_x = increment.x*cosf(yawRad) - increment.z*sinf(yawRad);
	double advance_z = increment.z*cosf(yawRad) + increment.x*sinf(yawRad);
	
	//double absx = cosf(pitchRad)*(advance_x) + sinf(pitchRad)*(advance_x);
	double absx = advance_x;
	double absy = increment.z*sinf(pitchRad) + increment.y; //y is incremented in Z because key W increases Z
	//double absz = cosf(pitchRad)*(advance_z) + sinf(pitchRad)*(advance_z);
	double absz = advance_z;

	incAbsPos(Vec3GLf(absx, absy, absz));

}


Camera::~Camera()
{
}
