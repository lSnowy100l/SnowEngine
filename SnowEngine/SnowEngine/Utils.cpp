#include "Utils.h"

// Binary aritmetic operators
Vec3GLf& operator+(Vec3GLf v1, const Vec3GLf& v2)
{
	v1 += v2;
	return v1;
}

Vec3GLf& operator-(Vec3GLf v1, const Vec3GLf& v2)
{
	v1 -= v2;
	return v1;
}

Vec3GLf& operator*(Vec3GLf v, GLfloat s)
{
	v *= s;
	return v;
}

Vec3GLf& operator/(Vec3GLf v, GLfloat s)
{
	v /= s;
	return v;
}

// Compound assignment operators
Vec3GLf & Vec3GLf::operator+=(const Vec3GLf& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3GLf & Vec3GLf::operator-=(const Vec3GLf& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3GLf & Vec3GLf::operator*=(GLfloat s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vec3GLf & Vec3GLf::operator/=(GLfloat s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

// Comparison operators
bool Vec3GLf::operator==(const Vec3GLf& v) {
	return x == v.x && y == v.y && z == v.z;
}

bool Vec3GLf::operator!=(const Vec3GLf& v) {
	return !(*this == v);
}

// Stream extraction operators
std::ostream& operator<<(std::ostream& os, Vec3GLf& v)
{
	return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}