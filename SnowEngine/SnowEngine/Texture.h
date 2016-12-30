#pragma once

#include <stdio.h>
#include "common.h"

class Texture
{
private:
	GLuint _textureId;
public:
	Texture(const char* filePath);
	inline GLuint getId() { return _textureId; }
	~Texture();
};

