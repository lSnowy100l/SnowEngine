#include "Player.h"

Player::Player(Camera * camera, ChunkManager * chk_manager, World * w, Vec3GLf position) :
	_player_cam(camera),
	_chk_manager(chk_manager),
	_world(w),
	Entity(position, PLAYER_MOVEMENT_FORCE, PLAYER_MASS)
{
	//REMEMBER TO CHECK SURROUNDINGS INITIALLY!!!
	this->_in_air = true;

	for (bool b : spec_keys) b = false;
	for (bool b : action_spec_keys) b = false;
}

bool Player::isTouching(Vec3GLf position)
{
	return this->_chk_manager->getBlockAt((unsigned)position.x, (unsigned)position.y, (unsigned)position.z) != NULL;
}

void Player::receiveInput(GLFWwindow* window, GLfloat delta_time) {
	Vec3GLf forceVector(0, 0, 0);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		forceVector.z -= 1;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		forceVector.x -= 1;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		forceVector.z += 1;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		forceVector.x += 1;

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) spec_keys[MY_X_KEY] = true;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE && spec_keys[MY_X_KEY]) handle_key_actions_after_release(MY_X_KEY);

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) spec_keys[MY_TAB_KEY] = true;
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && spec_keys[MY_TAB_KEY]) handle_key_actions_after_release(MY_TAB_KEY);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) spec_keys[MY_T_KEY] = true;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE && spec_keys[MY_T_KEY]) handle_key_actions_after_release(MY_T_KEY);

	// Converts absolute movement vector to relative movement
	this->computeMovementVector(forceVector);
	forceVector *= _movement_force;
	applyForce(forceVector);

	//Jump code
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS /*&& !_in_air*/) {
		applyForce(Vec3GLf(0, JUMP_FORCE, 0));
		_in_air = true;
	}
}

void Player::computeMovementVector(Vec3GLf& forceVector) {
	GLfloat _pitchRad = DEG_TO_RAD * this->_player_cam->getPitch();
	GLfloat _yawRad = DEG_TO_RAD * this->_player_cam->getYaw();

	forceVector = forceVector.normalized();
	Vec3GLf absForce(0, 0, 0);

	if (this->_abs_movement_mode) {
		//Absolute movement
		absForce.x = forceVector.x*cosf(_yawRad) - forceVector.z*sinf(_yawRad);
		absForce.y = 0;
		absForce.z = forceVector.z*cosf(_yawRad) + forceVector.x*sinf(_yawRad);
	}
	else {
		//Relative movement
		absForce.x += forceVector.x * cosf(_yawRad);
		absForce.z += forceVector.x * sinf(_yawRad);
		absForce.y += forceVector.y + forceVector.z * sinf(_pitchRad);;
		absForce.x += cosf(_pitchRad) * (-forceVector.z * sinf(_yawRad));
		absForce.z += cosf(_pitchRad) * forceVector.z * cosf(_yawRad);
	}
	forceVector = absForce;
}

void Player::externalForcesOnPlayer()
{
	//Gravitational force
	/*Vec3GLf curr_pos = this->_position;
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
	}*/
	this->_velocity.y -= this->_world->getWorldGravity();
}

void Player::additionalMovementUpdates(GLfloat deltaTime) {
	/*Vec3GLf camVel = _velocity;
	camVel *= deltaTime;
	this->_player_cam->incAbsPos(camVel);*/
	Vec3GLf camPos = _position;
	camPos.y += PLAYER_HEIGHT;
	_player_cam->setPosition(camPos);
}

void Player::handle_key_actions_after_release(GLuint key) {
	switch (key) {
	case MY_X_KEY: if (action_spec_keys[MY_X_KEY]) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case MY_TAB_KEY: if (action_spec_keys[MY_TAB_KEY]) this->_movement_force = DEBUG_SPEED; else this->_movement_force = PLAYER_MOVEMENT_FORCE;
		break;
	case MY_T_KEY: if (action_spec_keys[MY_T_KEY]) this->_abs_movement_mode = true; else this->_abs_movement_mode = false;
	}
	spec_keys[key] = false;
	action_spec_keys[key] = !action_spec_keys[key];
}

Player::~Player()
{
}
