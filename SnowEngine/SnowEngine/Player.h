#pragma once

#include <iostream>

#include "Camera.h"
#include "InputReceiver.h"
#include "ChunkManager.h"
#include "Window.h"
#include "World.h"

#define NEIGHBOURHOOD 3
#define PLAYER_HEIGHT 7 //2 blocks
#define PLAYER_SPEED 2.0f
#define DEBUG_SPEED 10.0f
#define N_PR_KEYS 16

//Special keys defines
#define MY_X_KEY 0 //Wireframe mode
#define MY_TAB_KEY 1 //Speed mode
#define MY_T_KEY 2 //Jetpack mode

class Player : public InputReceiver {
private:
	Camera * _player_cam;
	ChunkManager * _chk_manager;
	World * _world;
	Vec3GLf _velocity = Vec3GLf(0, 0, 0);
	Vec3GLf _position;
	GLfloat _movementSpeed = PLAYER_SPEED;
	bool _in_air;
	bool _abs_movement_mode = true;
	bool spec_keys[N_PR_KEYS];
	bool action_spec_keys[N_PR_KEYS];
public:
	Player(Camera * camera, ChunkManager * chk_manager, World * w, Vec3GLf position);
	bool isTouching(Vec3GLf position);
	void sendInput(GLFWwindow* window, GLfloat delta_time);
	void computeMovementVector();
	void externalForcesOnPlayer();
	void updatePlayerMovement(GLfloat deltaTime);
	void handle_key_actions_after_release(GLuint key);
	~Player();
};

