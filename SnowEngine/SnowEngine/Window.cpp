#include "Window.h"

Window::Window(int width, int height, const char* title)
{
	setWindowHints();
	_window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(),nullptr);
	setWindowCallbacks();
	glfwGetFramebufferSize(_window, &width, &height);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1); // To avoid tearing
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(_window, &lxpos, &lypos);
	glfwSetWindowUserPointer(_window, this);
	glEnable(GL_DEPTH_TEST);

	for (bool b : spec_keys) b = false;
	for (bool b : action_spec_keys) b = false;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Window::update() {
	glClearColor(.5, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lastFrame = newFrame;
	newFrame = glfwGetTime();
	deltaTime = newFrame - lastFrame;
	processKeyInputs();
	_renderer->renderAll();
	glFinish();
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window::processKeyInputs() {

	
	if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0, 0, -this->current_speed*deltaTime));
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(-this->current_speed*deltaTime, 0, 0));
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0, 0, this->current_speed*deltaTime));
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(this->current_speed*deltaTime, 0, 0));
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0, this->current_speed*deltaTime, 0));
	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_renderer->getCamera()->incRelPos(Vec3GLf(0, -this->current_speed*deltaTime, 0));
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, 1);

	if (glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS) spec_keys[MY_X_KEY] = true;
	if (glfwGetKey(_window, GLFW_KEY_X) == GLFW_RELEASE && spec_keys[MY_X_KEY]) handle_key_actions_after_release(MY_X_KEY);

	if (glfwGetKey(_window, GLFW_KEY_TAB) == GLFW_PRESS) spec_keys[MY_TAB_KEY] = true;
	if (glfwGetKey(_window, GLFW_KEY_TAB) == GLFW_RELEASE && spec_keys[MY_TAB_KEY]) handle_key_actions_after_release(MY_TAB_KEY);

}

void Window::handle_key_actions_after_release(GLuint key) {
	switch (key) {
	case MY_X_KEY: if (action_spec_keys[MY_X_KEY]) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case MY_TAB_KEY: if (action_spec_keys[MY_TAB_KEY]) this->current_speed = CAM_SPEED_NORM; else this->current_speed = CAM_SPEED_FAST;
		break;
	}
	spec_keys[key] = false;
	action_spec_keys[key] = !action_spec_keys[key];
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
	c->incPitch((ypos - w->lypos) * SENSIBILITY_Y);
	c->incYaw((xpos - w->lxpos) * SENSIBILITY_X);
	w->lypos = ypos;
	w->lxpos = xpos;
}

void Window::setWindowCallbacks() {
	glfwSetCursorPosCallback(_window, cursorCallback);
}