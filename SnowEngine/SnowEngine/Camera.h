#pragma once

#include "Vec3GLf.h"
#include "Mat4GLf.h"

class Camera
{
private:
	Vec3GLf _position, _lookAt;
	Mat4GLf _projectionMatrix;
public:
	Camera(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar);
	inline Vec3GLf getPosition() { return _position; }
	inline Vec3GLf getLookAt() { return _lookAt; }
	inline Mat4GLf getTranslationMatrix() { return Mat4GLf::translationMatrix(-_position); }
	inline Mat4GLf getProjectionMatrix() { return _projectionMatrix; }
	inline void incPosition(Vec3GLf increment) { _position += increment; }
	~Camera();
};

