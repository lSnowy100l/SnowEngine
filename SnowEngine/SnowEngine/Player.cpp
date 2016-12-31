#include "Player.h"

Player::Player(Camera * camera, ChunkManager * chk_manager, World * w, Vec3GLf position)
{
	this->_player_cam = camera;
	this->_chk_manager = chk_manager;
	this->_world = w;
	this->_position = position;
	this->_velocity.reset();
	this->_abs_movement_mode = true;

	//REMEMBER TO CHECK SURROUNDINGS INITIALLY!!!
	this->_in_air = true;

	for (bool b : spec_keys) b = false;
	for (bool b : action_spec_keys) b = false;
}

bool Player::isTouching(Vec3GLf position)
{
	if(this->_chk_manager->getBlockAt((unsigned)position.x, (unsigned)position.y, (unsigned)position.z) != NULL) return true;
	return false;
}

void Player::sendInput(GLFWwindow* window, GLfloat delta_time) {
	Vec3GLf movementVector(0, 0, 0);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movementVector.z -= 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movementVector.x -= 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movementVector.z += 1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movementVector.x += 1;

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) spec_keys[MY_X_KEY] = true;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE && spec_keys[MY_X_KEY]) handle_key_actions_after_release(MY_X_KEY);

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) spec_keys[MY_TAB_KEY] = true;
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && spec_keys[MY_TAB_KEY]) handle_key_actions_after_release(MY_TAB_KEY);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) spec_keys[MY_T_KEY] = true;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE && spec_keys[MY_T_KEY]) handle_key_actions_after_release(MY_T_KEY);


	_velocity = movementVector.normalized();
	_velocity *= _movementSpeed;
	this->computeMovementVector();
	//this->externalForcesOnPlayer();
	this->updatePlayerMovement(delta_time);
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

void Player::computeMovementVector()
{

	double _pitchRad = DEG_TO_RAD * this->_player_cam->getPitch();
	double _yawRad = DEG_TO_RAD * this->_player_cam->getYaw();

	GLfloat absx = 0, absy = 0, absz = 0;

	if (this->_abs_movement_mode) {
		//Absolute movement
		absx = _velocity.x*cosf(_yawRad) - _velocity.z*sinf(_yawRad);
		absy = 0;
		absz = _velocity.z*cosf(_yawRad) + _velocity.x*sinf(_yawRad);
	}
	else {
		//Relative movement
		absx += _velocity.x * cosf(_yawRad);
		absz += _velocity.x * sinf(_yawRad);
		absy += _velocity.y + _velocity.z * sinf(_pitchRad);;
		absx += cosf(_pitchRad) * (-_velocity.z * sinf(_yawRad));
		absz += cosf(_pitchRad) * _velocity.z * cosf(_yawRad);
	}
	_velocity.x = absx;
	_velocity.y = absy;
	_velocity.z = absz;
}


void Player::externalForcesOnPlayer()
{
	//Gravitational force
	Vec3GLf curr_pos = this->_position;
	curr_pos.y -= 1;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			curr_pos.x = this->_position.x + i;
			curr_pos.z = this->_position.z + j;
			if (this->isTouching(curr_pos)) {
				this->_velocity.y = 0;
				//Add jumping code here
				return;
			}
		}
	}
	this->_velocity.y -= this->_world->getWorldGravity();
}

void Player::updatePlayerMovement(GLfloat deltaTime) {
	_position.x += _velocity.x*deltaTime;
	_position.y += _velocity.y*deltaTime;
	_position.z += _velocity.z*deltaTime;

	this->_player_cam->incAbsPos(_velocity);
}

void Player::handle_key_actions_after_release(GLuint key) {
	switch (key) {
	case MY_X_KEY: if (action_spec_keys[MY_X_KEY]) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case MY_TAB_KEY: if (action_spec_keys[MY_TAB_KEY]) this->_movementSpeed = DEBUG_SPEED; else this->_movementSpeed = PLAYER_SPEED;
		break;
	case MY_T_KEY: if (action_spec_keys[MY_T_KEY]) this->_abs_movement_mode = true; else this->_abs_movement_mode = false;
	}
	spec_keys[key] = false;
	action_spec_keys[key] = !action_spec_keys[key];
}

Player::~Player()
{
}
