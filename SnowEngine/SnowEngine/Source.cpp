#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Chunk.h"
#include "Renderer.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "First Window"

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "Error: %s\n", "Failed to initialize GLFW library.");
		return 1;
	}

	fprintf(stdout, "Status: Using GLFW version %s\n", glfwGetVersionString());
	Window* w = new Window(WIDTH, HEIGHT, TITLE);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		system("PAUSE");
		return 2;
	}
	
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	glewExperimental = GL_TRUE;

	while (w->shouldClose() == 0) {
		w->update();
	}

	delete w;
	glfwTerminate();
	return 0;
}