#pragma once

#include "GLFW/glfw3.h"

class InputReceiver {
public:
	virtual void sendInput(GLFWwindow* window) = 0;
};

