#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MasterRenderer.h"
#include "InputReceiver.h"

#define SENSIBILITY_X 0.2f
#define SENSIBILITY_Y 0.3f


class Window
{
private:
	GLFWwindow* _window;
	MasterRenderer* _renderer;
	double lxpos, lypos;
	GLfloat lastFrame = 0, newFrame = 0, deltaTime = 0;
	std::vector<InputReceiver*> inputReceivers;
public:
	Window(int width, int height, const char* title);
	void update();
	inline int shouldClose() { return glfwWindowShouldClose(_window); }
	void processKeyInputs();
	inline void addInputReceiver(InputReceiver* ir) { inputReceivers.push_back(ir); }
	inline void associateRenderer(MasterRenderer* renderer) { _renderer = renderer; }
	friend void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	double getDeltaTime() { return deltaTime; }
	~Window();
private:
	void setWindowHints();
	void setWindowCallbacks();
};

