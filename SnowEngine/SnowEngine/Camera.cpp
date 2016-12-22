#include "Camera.h"



Camera::Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar) : _position(Vec3GLf()), _lookAt(Vec3GLf()), _projectionMatrix(Mat4GLf::projectionMatrix(width, height, fov, znear, zfar))
{
}


Camera::~Camera()
{
}
