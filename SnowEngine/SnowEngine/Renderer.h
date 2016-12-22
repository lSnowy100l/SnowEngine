#pragma once

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <vector>

class Renderer
{
protected:
	GLuint _vertexShaderId, _fragmentShaderId, _programId;
protected:
	GLuint genShader(const char* filePath, GLenum type);
	void clear();
private:
	virtual void bindAtributes() = 0;
};

