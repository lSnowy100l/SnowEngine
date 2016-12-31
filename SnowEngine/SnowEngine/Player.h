#pragma once

#include <iostream>

#include "Camera.h"
#include "InputReceiver.h"
#include "ChunkManager.h"
#include "Window.h"
#include "World.h"

#define NEIGHBOURHOOD 3
#define PLAYER_HEIGHT 7 //2 blocks
#define PLAYER_SPEED 4.0f

class Player : public InputReceiver {
private:
	Camera * _player_cam;
	ChunkManager * _chk_manager;
	World * _world;
	Vec3GLf _velocity = Vec3GLf(0, 0, 0);
	GLfloat _movementSpeed = PLAYER_SPEED;
public:
	Player(Camera * camera, ChunkManager * chk_manager, World * w);
	bool isTouching(Vec3GLf position);
	void sendInput(GLFWwindow* window);
	void externalForcesOnPlayer();
	void updatePlayerMovement(GLfloat deltaTime);
	~Player();
};

