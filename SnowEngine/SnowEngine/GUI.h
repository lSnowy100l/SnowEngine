#pragma once

#include "GL/glew.h"
#include "Texture.h"

class GUI
{
private:
	GLuint _vaoId;
	GLuint _vboId[2];
	Texture* _texture;
public:
	GUI();
	inline GLuint getVaoId() { return _vaoId; }
	inline Texture* getTexture() { return _texture; }
	~GUI();
};

