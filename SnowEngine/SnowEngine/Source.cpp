#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Chunk.h"
#include "MasterRenderer.h"
#include "ChunkManager.h"
#include "Player.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "First Window"

int main() {
	std::cout << "Verifying 64 bits compatibility ... ";
	((sizeof(int *) == 8)) ? fprintf(stdout, "Correct\n") : terror("System is not 64 bits, exiting.", -1);
	
	// GLFW Libraries initialization
	if (!glfwInit()) terror("Failed to initialize GLFW library, exiting", -1);

	//Show version
	fprintf(stdout, "%s\n", glfwGetVersionString());

	Window* gameWindow = new Window(WIDTH, HEIGHT, TITLE);

	// GLEW Libraries initialization
	GLenum err = glewInit();
	if (err != GLEW_OK) terror((char *)glewGetErrorString(err), 2);

	glewExperimental = GL_TRUE;

	
	Camera * camera = new Camera(WIDTH, HEIGHT, 70.0f, 0.01f, 1000.0f, Vec3GLf(70,70,70));
	
	MasterRenderer * renderer = new MasterRenderer(camera);
	ChunkRenderer * chunk_renderer = new ChunkRenderer(renderer, "vertexShader.vert", "fragmentShader.frag");
	renderer->addRenderer(chunk_renderer);
	gameWindow->associateRenderer(renderer);
	ChunkManager * chunk_manager = new ChunkManager(chunk_renderer);
	
	World * planet_earth = new World(9.8f);

	Player * p = new Player(camera, chunk_manager, planet_earth, Vec3GLf(70, 70-PLAYER_HEIGHT, 70));
	gameWindow->addInputReceiver(p);
	planet_earth->addEntity(p);

	// Main game loop
	while (gameWindow->shouldClose() == GL_FALSE) {
		gameWindow->update();
		chunk_manager->update();
		planet_earth->update(gameWindow->getDeltaTime());
	}

	delete chunk_manager;
	delete gameWindow;
	delete renderer;
	delete p;

	glfwTerminate();

	return 0;
}