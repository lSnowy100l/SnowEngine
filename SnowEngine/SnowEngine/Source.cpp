#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Chunk.h"
#include "MasterRenderer.h"

#define WIDTH 1280
#define HEIGHT 960
#define TITLE "First Window"

Vec3GLf operator+(Vec3GLf v1, const Vec3GLf& v2) {
	v1 += v2;
	return v1;
}

std::ostream& operator<<(std::ostream& os, Vec3GLf& v) {
	return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

int main() {
	// GLFW Libraries initialization
	if (!glfwInit()) {
		fprintf(stderr, "Error: %s\n", "Failed to initialize GLFW library.");
		return 1;
	}

	Window* w = new Window(WIDTH, HEIGHT, TITLE);

	// GLEW Libraries initialization
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return 2;
	}

	glewExperimental = GL_TRUE;

	Camera* camera = new Camera(WIDTH, HEIGHT, 90, 0.01, 1000);
	
	MasterRenderer* renderer = new MasterRenderer(camera);
	ChunkRenderer* cr = new ChunkRenderer(renderer, "vertexShader.vert", "fragmentShader.frag");
	renderer->addRenderer(cr);
	w->associateRenderer(renderer);

	int i = 0;
	while (w->shouldClose() == 0) {
		camera->incPosition(Vec3GLf(0, 0, 0.005));
		w->update();
	}

	delete w;
	delete renderer;

	glfwTerminate();
	return 0;
}