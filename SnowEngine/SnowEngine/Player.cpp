#include "Player.h"

Player::Player(Camera * camera, ChunkManager * chk_manager, World * w)
{
	this->_player_cam = camera;
	this->_chk_manager = chk_manager;
	this->_world = w;
	this->_acceleration.x = 0;
	this->_acceleration.y = 0;
	this->_acceleration.z = 0;
}

bool Player::isTouching(Vec3GLf position)
{
	if(this->_chk_manager->getBlockAt((unsigned)position.x, (unsigned)position.y, (unsigned)position.z) != NULL) return true;
	return false;
}

void Player::externalForcesOnPlayer()
{
	//Gravitational force
	Vec3GLf curr_pos = this->_player_cam->getPosition();
	curr_pos.y -= PLAYER_HEIGHT;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			curr_pos.x = this->_player_cam->getPosition().x + i;
			curr_pos.z = this->_player_cam->getPosition().z + j;
			if (this->isTouching(curr_pos)) {
				this->_acceleration.reset();
				return;
			}
		}
	}
	this->_acceleration.y -= this->_world->getWorldGravity();
}

void Player::updatePlayerMovement(double delta_time)
{
	this->externalForcesOnPlayer();
	this->_player_cam->updateMovementCamera(delta_time, &this->_acceleration);

}

Player::~Player()
{
}
