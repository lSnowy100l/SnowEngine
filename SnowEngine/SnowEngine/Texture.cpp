#include "Texture.h"


Texture::Texture(const char* filePath)
{
	std::vector<unsigned char> data;
	unsigned width, height;
	unsigned error = lodepng::decode(data, width, height, filePath);

	if (error) terror(lodepng_error_text(error), error);

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);

	//Sets the interpolation mode for holes between the texture and the overall geometry.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Sets the interpolation mode for fragments between two texture pixels (nearest for sharp edges)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//Unbids the current texture.
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_textureId);
}
