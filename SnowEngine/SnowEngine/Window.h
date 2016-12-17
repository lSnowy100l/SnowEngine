#pragma once

#include <GLFW/glfw3.h>

#include "ChunkRenderer.h"

class Window
{
private:
	GLFWwindow* _window;
	ChunkRenderer* _chunk_renderer;
public:
	Window(int width, int height, const char* title);
	inline void assignChunkRenderer(ChunkRenderer* chunkRenderer) { _chunk_renderer = chunkRenderer;) }
	void update();
	inline int shouldClose() { return glfwWindowShouldClose(_window); }
	~Window();
private:
	void setWindowHints();
	void setWindowCallbacks();
};

