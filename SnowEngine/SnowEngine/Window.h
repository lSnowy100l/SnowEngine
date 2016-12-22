#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MasterRenderer.h"

class Window
{
private:
	GLFWwindow* _window;
	MasterRenderer* _renderer;
public:
	Window(int width, int height, const char* title);
	void update();
	inline int shouldClose() { return glfwWindowShouldClose(_window); }
	inline void associateRenderer(MasterRenderer* renderer) { _renderer = renderer; }
	~Window();
private:
	void setWindowHints();
	void setWindowCallbacks();
};

