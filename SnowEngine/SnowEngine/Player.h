#pragma once

#include <iostream>

#include "Camera.h"
#include "ChunkManager.h"
#include "World.h"

#define NEIGHBOURHOOD 3
#define PLAYER_HEIGHT 7 //2 blocks

class Player
{
private:
	Camera * _player_cam;
	ChunkManager * _chk_manager;
	World * _world;
	Vec3GLf _acceleration;
public:
	Player(Camera * camera, ChunkManager * chk_manager, World * w);
	bool isTouching(Vec3GLf position);
	void externalForcesOnPlayer();
	void updatePlayerMovement(double delta_time);
	~Player();
};

