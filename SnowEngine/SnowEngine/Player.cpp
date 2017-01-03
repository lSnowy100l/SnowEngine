#include "Player.h"

Player::Player(Camera * camera, ChunkManager * chk_manager, Vec3GLf position) :
	_player_cam(camera),
	Entity(position, PLAYER_MOVEMENT_FORCE, PLAYER_MASS, chk_manager)
{
	//REMEMBER TO CHECK SURROUNDINGS INITIALLY!!!
	this->_in_air = true;

	for (bool b : spec_keys) b = false;
	for (bool b : action_spec_keys) b = false;
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !_in_air) {
		applyForce(Vec3GLf(0, JUMP_FORCE, 0));
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


void Player::updateMovement(GLfloat delta_time)
{
	_forces /= _mass;

	_velocity.x += _forces.x;
	_velocity.z += _forces.z;

	

	_position.x += _velocity.x*delta_time;
	_position.z += _velocity.z*delta_time;

	//If the y-position is not ocuppied (this should be done for x and z as well)
	if (!isOccupied(Vec3GLf(_position.x, (_position.y + (_velocity.y+_forces.y)*delta_time)-PLAYER_HEIGHT, _position.z))) {
		_velocity.y += _forces.y;
		_position.y += _velocity.y*delta_time;
		this->_in_air = true;
	}
	else {
		this->_in_air = false;
		_velocity.y = 0;
	}
	
	std::cout << "F: " << _forces << std::endl;

	_forces.reset();

	Vec3GLf camPos = _position;
	camPos.y += PLAYER_HEIGHT;
	_player_cam->setPosition(camPos);
}

bool Player::isAffectedByGravity()
{
	if (this->_abs_movement_mode) return true;
	return false;
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
