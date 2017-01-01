#pragma once

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define PI 3.1415927410125732421875f
#define DEG_TO_RAD 0.01745329238474369049072265625f

struct Vec3GLf
{
	// Public variables
	GLfloat x, y, z;

	// Constructors
	Vec3GLf() : x(0), y(0), z(0) {}
	Vec3GLf(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

	// Binary aritmetic operators
	friend Vec3GLf& operator+(Vec3GLf v1, const Vec3GLf& v2);
	friend Vec3GLf& operator-(Vec3GLf v1, const Vec3GLf& v2);
	friend Vec3GLf& operator*(Vec3GLf v, GLfloat s);
	friend Vec3GLf& operator/(Vec3GLf v, GLfloat s);

	// Compound assignment operators
	Vec3GLf& operator+=(const Vec3GLf& v);
	Vec3GLf& operator-=(const Vec3GLf& v);
	Vec3GLf& operator*=(GLfloat v);
	Vec3GLf& operator/=(GLfloat s);

	Vec3GLf operator-() {
		return Vec3GLf(-x, -y, -z);
	}

	// Comparison operators
	bool operator==(const Vec3GLf& v);
	bool operator!=(const Vec3GLf& v);

	// Stream extraction operators
	friend std::ostream& operator<<(std::ostream& os, Vec3GLf& v);

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
		if (l != 0) return Vec3GLf(x / l, y / l, z / l);
		return Vec3GLf(0, 0, 0);
	}
	static Vec3GLf toVector(GLfloat pitch, GLfloat yaw) {
		float radPitch = pitch * DEG_TO_RAD, radYaw = yaw * DEG_TO_RAD;
		return Vec3GLf(-sinf(radYaw)*cosf(radPitch), sinf(radPitch), cosf(radYaw)*cosf(radPitch));
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