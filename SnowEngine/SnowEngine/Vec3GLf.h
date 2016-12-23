#pragma once

#include <GL/glew.h>
#include <ostream>
#include <cmath>

#define DEG_TO_RAD 0.0174533

struct Vec3GLf {
	GLfloat x, y, z;
	Vec3GLf() : x(0), y(0), z(0) {}
	Vec3GLf(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	Vec3GLf& operator+=(const Vec3GLf& v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	Vec3GLf operator-() {
		return Vec3GLf(-x, -y, -z);
	}

	float length() {
		return sqrtf(x*x + y*y + z*z);
	}
	Vec3GLf normalized() {
		float l = length();
		return Vec3GLf(x/l, y/l, z/l);
	}
	static Vec3GLf toVector(GLfloat pitch, GLfloat yaw) {
		double radPitch = pitch * DEG_TO_RAD, radYaw = yaw * DEG_TO_RAD;
		return Vec3GLf(cosf(radYaw)*cosf(radPitch), sinf(radPitch), sinf(radYaw)*cosf(radPitch));
	}
};