#pragma once
#include <Windows.h>
#include <iostream>
#include "Vec3GLf.h"

const char data_directory[MAX_PATH] = "./DATA/";

std::ostream& operator<<(std::ostream& os, Vec3GLf& v);

void terror(const char * msg, int error);

