#pragma once

#include "GLFW/glfw3.h"

class InputReceiver {
public:
	virtual void receiveInput(GLFWwindow* window, GLfloat delta_time) = 0;
};

