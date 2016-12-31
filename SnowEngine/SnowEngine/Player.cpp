#include "Player.h"

Player::Player(Camera * camera, ChunkManager * chk_manager, World * w)
{
	this->_player_cam = camera;
	this->_chk_manager = chk_manager;
	this->_world = w;
	this->_velocity.x = 0;
	this->_velocity.y = 0;
	this->_velocity.z = 0;
}

bool Player::isTouching(Vec3GLf position)
{
	if(this->_chk_manager->getBlockAt((unsigned)position.x, (unsigned)position.y, (unsigned)position.z) != NULL) return true;
	return false;
}

void Player::sendInput(GLFWwindow* window) {
	Vec3GLf movementVector(0, 0, 0);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movementVector.z -= 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movementVector.x -= 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movementVector.z += 1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movementVector.x += 1;

	_velocity = movementVector.normalized();
	_velocity *= _movementSpeed;
	/*
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!action_spec_keys[MY_T_KEY]) {
			//If jetpack mode is off,
			if (!window->getCamera()->getStartJump() && !_renderer->getCamera()->getJump()) {
				_renderer->getCamera()->setJump(true);
				_renderer->getCamera()->setStartJump(true);
				_renderer->getCamera()->moveCamera(Vec3GLf(0, JUMP_FORCE, 0));
			}
		}
		else {
			//If it is not
			_renderer->getCamera()->moveCamera(Vec3GLf(0, _renderer->getCamera()->getCurrentSpeed(), 0));
		}
	}
	*/

}

void Player::externalForcesOnPlayer()
{
	//Gravitational force
	/*Vec3GLf curr_pos = this->_player_cam->getPosition();
	curr_pos.y -= PLAYER_HEIGHT;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			curr_pos.x = this->_player_cam->getPosition().x + i;
			curr_pos.z = this->_player_cam->getPosition().z + j;
			if (this->isTouching(curr_pos)) {
				this->_velocity.reset();
				this->_player_cam->setStartJump(false);
				this->_player_cam->setJump(false);
				return;
			}
		}
	}
	this->_velocity.y -= this->_world->getWorldGravity();*/
}

void Player::updatePlayerMovement(GLfloat deltaTime) {
	this->externalForcesOnPlayer();
	this->_player_cam->relativeMovement(deltaTime, &this->_velocity);
}

Player::~Player()
{
}
