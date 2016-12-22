#include "Window.h"



Window::Window(int width, int height, const char* title)
{
	setWindowHints();
	setWindowCallbacks();
	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwGetFramebufferSize(_window, &width, &height);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Window::update() {
	glClear(GL_COLOR_BUFFER_BIT);
	_renderer->renderAll();
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

Window::~Window()
{

}

void Window::setWindowHints() {
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
}

void Window::setWindowCallbacks() {
	//TODO
}