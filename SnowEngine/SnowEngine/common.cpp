#include "common.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, Vec3GLf& v) {
	return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

void terror(const char * msg, int error) {
	fprintf(stderr, "ERROR [%d]: %s\n", error, msg);
	getchar();
	exit(error);
}