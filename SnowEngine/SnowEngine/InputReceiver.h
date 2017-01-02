#pragma once

#include "GLFW/glfw3.h"

class InputReceiver
{
public:
	virtual void receiveInput(GLFWwindow* window) = 0;
};

