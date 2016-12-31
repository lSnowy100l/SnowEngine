#pragma once

#include <GL/glew.h>
#include <ostream>
#include <math.h>

#define PI 3.1415927410125732421875f
#define DEG_TO_RAD 0.01745329238474369049072265625f

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

	Vec3GLf& operator*=(GLfloat v) { // For scalar multiplication
		this->x *= v;
		this->y *= v;
		this->z *= v;
		return *this;
	}

	Vec3GLf operator-() {
		return Vec3GLf(-x, -y, -z);
	}
	bool operator==(const Vec3GLf& v) {
		return x == v.x && y == v.y && z == v.z;
	}
	GLfloat length() {
		return (GLfloat) sqrtf(x*x + y*y + z*z);
	}
	void reset() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3GLf normalized() {
		GLfloat l = length();
		if(l != 0) return Vec3GLf(x / l, y / l, z / l);
		return Vec3GLf(0, 0, 0);
	}
	static Vec3GLf toVector(GLfloat pitch, GLfloat yaw) {
		float radPitch = pitch * DEG_TO_RAD, radYaw = yaw * DEG_TO_RAD;
		return Vec3GLf(-sinf(radYaw)*cosf(radPitch),sinf(radPitch), cosf(radYaw)*cosf(radPitch));
	}

};


struct Vec3GLui {
	GLuint x, y, z;
	Vec3GLui() : x(0), y(0), z(0) {}
	Vec3GLui(GLuint x, GLuint y, GLuint z) : x(x), y(y), z(z) {}
	bool operator==(const Vec3GLui& v) {
		return x == v.x && y == v.y && z == v.z;
	}
};