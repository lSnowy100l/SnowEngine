#include "Camera.h"



Camera::Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar) : _projectionMatrix(Mat4GLf::projectionMatrix(width, height, fov, znear, zfar))
{
}

Vec3GLf Camera::getLookAt() {
	return Vec3GLf::toVector(_pitch, _yaw);
}

Mat4GLf Camera::getRotationMatrix() {
	/*Vec3GLf lookAt = Vec3GLf::toVector(_pitch, _yaw);
	Vec3GLf rightVector = Vec3GLf::toVector(0, _yaw - 90);*/
	Vec3GLf lookAt(1, 0, 0), rightVector(0, 0, 1);
	Vec3GLf upVector = Vec3GLf(
		rightVector.y*lookAt.z - rightVector.z*lookAt.y,
		rightVector.z*lookAt.x - rightVector.x*lookAt.z,
		rightVector.x*lookAt.y - rightVector.y*lookAt.x);
	system("CLS");
	std::cout << "LookAt: " << lookAt.x << ", " << lookAt.y << ", " << lookAt.z << std::endl;
	std::cout << "RightAt: " << rightVector.x << ", " << rightVector.y << ", " << rightVector.z << std::endl;
	std::cout << "UpVector: " << upVector.x << ", " << upVector.y << ", " << upVector.z << std::endl;
	Mat4GLf rotationMatrix = Mat4GLf::viewRotationMatrix(lookAt, rightVector, upVector);
	return rotationMatrix;
}

void Camera::incRelPos(Vec3GLf increment) {
	double yawRad = _yaw*DEG_TO_RAD;
	incAbsPos(Vec3GLf(increment.x*cosf(yawRad) + increment.z*sinf(yawRad), increment.y, increment.z*cosf(yawRad) - increment.x*sinf(yawRad)));
}
Camera::~Camera()
{
}
