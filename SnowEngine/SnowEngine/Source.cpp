#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Chunk.h"
#include "MasterRenderer.h"
#include "ChunkManager.h"
#include "common.h"

#define WIDTH 1280
#define HEIGHT 720
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
	camera->incAbsPos(Vec3GLf(70.0, 34.0, 70.0));
	
	MasterRenderer* renderer = new MasterRenderer(camera);
	ChunkRenderer* cr = new ChunkRenderer(renderer, "vertexShader.vert", "fragmentShader.frag");
	renderer->addRenderer(cr);
	w->associateRenderer(renderer);
	ChunkManager* cm = new ChunkManager(cr);

	while (w->shouldClose() == 0) {
		for (int i = -3; i <= 3; i++) {
			for (int j = -3; j <= 3; j++) {
				for (int k = -3; k <= 3; k++) {
					cm->setBlockAt((GLuint)camera->getPosition().x + i, (GLuint)camera->getPosition().y + j, (GLuint)camera->getPosition().z + k, 0);
				}
			}
		}
		
		cm->update();
		w->update();
	}

	delete cm;
	delete w;
	delete renderer;

	glfwTerminate();
	return 0;
}