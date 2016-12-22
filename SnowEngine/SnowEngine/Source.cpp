#define GLEW_STATIC
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Chunk.h"
#include "MasterRenderer.h"

#define WIDTH 800
#define HEIGHT 600
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

	MasterRenderer* renderer = new MasterRenderer("vertexShader.vert", "fragmentShader.frag", Vec3GLf(0, 0, 0));
	ChunkRenderer* cr = renderer->getChunkRenderer();
	w->associateRenderer(renderer);
	Chunk* c = new Chunk(1, 0, 2);

	while (w->shouldClose() == 0) {
		cr->addToRenderList(c);
		w->update();
	}

	c->saveToFile();
	delete w;
	delete renderer;

	glfwTerminate();
	return 0;
}