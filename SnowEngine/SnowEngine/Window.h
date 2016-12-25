#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MasterRenderer.h"

#define SENSIBILITY_X 0.2
#define SENSIBILITY_Y 0.3
#define N_PR_KEYS 3

//Special keys defines
#define MY_X_KEY 0

class Window
{
private:
	GLFWwindow* _window;
	MasterRenderer* _renderer;
	double lxpos, lypos;
	bool spec_keys[N_PR_KEYS];
	bool action_spec_keys[N_PR_KEYS];
public:
	Window(int width, int height, const char* title);
	void update();
	inline int shouldClose() { return glfwWindowShouldClose(_window); }
	void processKeyInputs();
	void handle_key_actions_after_release(GLuint key);
	inline void associateRenderer(MasterRenderer* renderer) { _renderer = renderer; }
	friend void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	~Window();
private:
	void setWindowHints();
	void setWindowCallbacks();
};

