#pragma once

#include "GL/glew.h"
#include "Texture.h"

class GUI
{
protected:
	GLuint _vaoId;
	GLuint _vboId[2];
	GLuint _vertexCount;
	Texture* _texture;
public:
	GUI(const char* filePath);
	inline GLuint getVaoId() { return _vaoId; }
	inline Texture* getTexture() { return _texture; }
	inline GLuint getVertexCount() { return _vertexCount; }
	~GUI();
};

