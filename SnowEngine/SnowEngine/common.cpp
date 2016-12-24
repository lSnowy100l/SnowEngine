#include <iostream>
#include "Vec3GLf.h"
using namespace std;

std::ostream& operator<<(std::ostream& os, Vec3GLf& v) {
	return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}