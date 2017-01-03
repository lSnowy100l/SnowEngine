#include "Window.h"

Window::Window(int width, int height, const char* title)
{
	setWindowHints();
	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (_window == nullptr) terror("Your graphics card does not support OpenGL 3.2", 1);
	setWindowCallbacks();
	glfwGetFramebufferSize(_window, &width, &height);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(_window, &lxpos, &lypos);
	glfwSetWindowUserPointer(_window, this);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Window::update()
{
	glClearColor(.5, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lastFrame = newFrame;
	newFrame = (GLfloat) glfwGetTime();
	deltaTime = newFrame - lastFrame;
	glfwPollEvents();
	processKeyInputs();
	_renderer->renderAll();
	glfwSwapBuffers(_window);
}

void Window::processKeyInputs()
{
	for (InputReceiver* ir : inputReceivers)
		ir->receiveInput(_window);

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, 1);
}

Window::~Window()
{

}

void Window::setWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	Window* w = (Window*) glfwGetWindowUserPointer(window);
	Camera* c = w->_renderer->getCamera();
	c->incPitch((GLfloat) (ypos - w->lypos) * SENSIBILITY_Y);
	c->incYaw((GLfloat) (xpos - w->lxpos) * SENSIBILITY_X);
	w->lypos = ypos;
	w->lxpos = xpos;
}

void Window::setWindowCallbacks()
{
	glfwSetCursorPosCallback(_window, cursorCallback);
}