#include "Window.h"

Window::Window(int width, int height, const char* title)
{
	setWindowHints();
	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	setWindowCallbacks();
	glfwGetFramebufferSize(_window, &width, &height);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(_window, &lxpos, &lypos);
	glfwSetWindowUserPointer(_window, this);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Window::update() {
	glClear(GL_COLOR_BUFFER_BIT);
	processKeyInputs();
	_renderer->renderAll();
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window::processKeyInputs() {
	if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0, 0, -0.1));
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(-0.1, 0, 0));
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0, 0, 0.1));
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0.1, 0, 0));
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		_renderer->getCamera()->incAbsPos(Vec3GLf(0, 0.1, 0));
	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_renderer->getCamera()->incAbsPos(Vec3GLf(0, -0.1, 0));
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, 1);
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

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	Window* w = (Window*) glfwGetWindowUserPointer(window);
	Camera* c = w->_renderer->getCamera();
	//c->incPitch((w->lypos - ypos) * SENSIBILITY_Y);
	c->incYaw((w->lxpos - xpos) * SENSIBILITY_Y);
	w->lypos = ypos;
	w->lxpos = xpos;
}

void Window::setWindowCallbacks() {
	glfwSetCursorPosCallback(_window, cursorCallback);
}