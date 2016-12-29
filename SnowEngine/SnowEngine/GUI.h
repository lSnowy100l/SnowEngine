#pragma once

#include "GL/glew.h"

class GUI
{
private:
	GLuint _vaoId;
	GLuint _vboId;
public:
	GUI();
	inline GLuint getVaoId() { return _vaoId; }
	~GUI();
};

