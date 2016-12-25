#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Chunk.h"
#include "MasterRenderer.h"
#include "common.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "First Window"

Vec3GLf operator+(Vec3GLf v1, const Vec3GLf& v2) {
	v1 += v2;
	return v1;
}

int main() {
	// GLFW Libraries initialization
	if (!glfwInit()) {
		fprintf(stderr, "Error: %_s\n", "Failed to initialize GLFW library.");
		return 1;
	}

	//Show version

	fprintf(stdout, "%s\n", glfwGetVersionString());

	Window* w = new Window(WIDTH, HEIGHT, TITLE);

	// GLEW Libraries initialization
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %_s\n", glewGetErrorString(err));
		return 2;
	}

	glewExperimental = GL_TRUE;

	Camera* camera = new Camera(WIDTH, HEIGHT, 70, 0.01, 1000);
	camera->incAbsPos(Vec3GLf(0.0, 0.0, 0.0));
	
	MasterRenderer* renderer = new MasterRenderer(camera);
	ChunkRenderer* cr = new ChunkRenderer(renderer, "vertexShader.vert", "fragmentShader.frag");
	renderer->addRenderer(cr);
	w->associateRenderer(renderer);
	std::vector<Chunk*> chunks;
	for (int i = 0; i <= 5; i++) {
		for (int j = 0; j <= 5; j++) {
			chunks.push_back(new Chunk(i, 0, j));
		}
	}

	while (w->shouldClose() == 0) {
		for (Chunk* c : chunks) {
			cr->addToRenderList(c);
		}
		w->update();
	}

	for (Chunk* c : chunks) {
		delete c;
	}
	delete w;
	delete renderer;

	glfwTerminate();
	return 0;
}