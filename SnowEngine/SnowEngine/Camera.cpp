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

	
	Vec3GLf forward_v = Vec3GLf::toVector(_pitch, _yaw);
	std::cout << _position << " @" << forward_v << endl;
	Vec3GLf left_v = Vec3GLf::toVector(0, _yaw + 90);


	//Vec3GLf lookAt(1, 0, 0), rightVector(0, 0, 1);
	Vec3GLf up_v = Vec3GLf::toVector(_pitch + 90, _yaw);
	
	Mat4GLf rotationMatrix = Mat4GLf::viewRotationMatrix(left_v, forward_v, up_v);
	return rotationMatrix;
}

void Camera::incRelPos(Vec3GLf increment) {
	double yawRad = _yaw*DEG_TO_RAD;
	incAbsPos(Vec3GLf(increment.x*cosf(yawRad) + increment.z*sinf(yawRad), increment.y, increment.z*cosf(yawRad) - increment.x*sinf(yawRad)));
}
Camera::~Camera()
{
}
