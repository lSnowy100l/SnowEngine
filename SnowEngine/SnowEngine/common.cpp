#include "common.h"

using namespace std;

void terror(const char * msg, int error) {
	fprintf(stderr, "ERROR [%d]: %s\n", error, msg);
	getchar();
	exit(error);
}

