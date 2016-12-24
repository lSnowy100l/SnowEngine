#pragma once

#include <GL/glew.h>
#include "Vec3GLf.h"

struct Mat4GLf {
	GLfloat data[16];
	Mat4GLf() {
		for (int i = 0; i < 16; i++) {
			data[i] = 0;
		}
	}
	static Mat4GLf projectionMatrix(GLfloat width, GLfloat height, GLfloat fov, GLfloat znear, GLfloat zfar) {
		GLfloat ar = width / height;
		Mat4GLf m;
		m.data[0] = 1 / (ar*tanf(fov/2));
		m.data[5] = 1 / tanf(fov / 2);
		m.data[10] = -(zfar + znear) / (zfar - znear);
		m.data[11] = -(2 * zfar*znear) / (zfar - znear);
		m.data[14] = -1;
		return m;
	}
	static Mat4GLf translationMatrix(Vec3GLf translation) {
		Mat4GLf m;
		m.data[0] = 1;
		m.data[5] = 1;
		m.data[10] = 1;
		m.data[15] = 1;
		m.data[3] = translation.x;
		m.data[7] = translation.y;
		m.data[11] = translation.z;
		return m;
	}
	static Mat4GLf viewRotationMatrix(Vec3GLf leftVector, Vec3GLf forwardVector, Vec3GLf upVector) {
		Mat4GLf m;
		m.data[0] = leftVector.x;
		m.data[1] = upVector.x;
		m.data[2] = forwardVector.x;
		m.data[4] = leftVector.y;
		m.data[5] = upVector.y;
		m.data[6] = forwardVector.y;
		m.data[8] = leftVector.z;
		m.data[9] = upVector.z;
		m.data[10] = forwardVector.z;
		m.data[15] = 1;
		return m;
	}
};