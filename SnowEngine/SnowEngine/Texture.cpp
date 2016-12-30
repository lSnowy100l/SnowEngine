#include "Texture.h"


Texture::Texture(const char* filePath)
{
	// Data read from the header of the BMP file
	GLubyte header[54]; // Each BMP file begins by a 54-bytes header
	GLuint dataPos;     // Position in the file where the actual data begins
	GLuint width, height;
	GLuint imageSize;   // = width*height*3
							  // Actual RGB data
	GLubyte * data;

	FILE * file = fopen(filePath, "rb");
	if (!file) terror("Image could not be opened\n", 1);

	if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') terror("Not a valid file format\n", 1);

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	data = new GLubyte[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	delete data;

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
