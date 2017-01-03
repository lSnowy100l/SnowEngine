#pragma once

#include <iostream>

#include "Camera.h"
#include "InputReceiver.h"
#include "ChunkManager.h"
#include "Window.h"
#include "Entity.h"
#include "World.h"

#define NEIGHBOURHOOD 3
#define PLAYER_HEIGHT 7 //2 blocks
#define PLAYER_MOVEMENT_FORCE 500.0f
#define DEBUG_SPEED 1000.0f
#define N_PR_KEYS 16
#define PLAYER_MASS 20

//Special keys defines
#define MY_X_KEY 0 //Wireframe mode
#define MY_TAB_KEY 1 //Speed mode
#define MY_T_KEY 2 //Jetpack mode

class Player :
	public InputReceiver,
	public Entity
{
private:
	Camera* _player_cam;
	ChunkManager* _chk_manager;
	World* _world;

	bool _abs_movement_mode = true;
	bool spec_keys[N_PR_KEYS];
	bool action_spec_keys[N_PR_KEYS];
public:
	Player(Camera * camera, ChunkManager * chk_manager, World * w, Vec3GLf position);
	bool isTouching(Vec3GLf position);
	void receiveInput(GLFWwindow * window) override;
	void computeMovementVector(Vec3GLf & movementVector);
	void externalForcesOnPlayer();
	void additionalMovementUpdates();
	void handle_key_actions_after_release(GLuint key);
	~Player();
};

