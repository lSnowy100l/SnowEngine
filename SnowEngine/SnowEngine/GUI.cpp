#include "GUI.h"



GUI::GUI(const char* file_path) :
	_texture(new Texture(file_path))
{
	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(2, &_vboId[0]);
	/*glBindVertexArray(_vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	GLfloat data[] = {
	0, 600,
	0, 0,
	600, 600,
	0, 0,
	600, 600,
	600, 0 };
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[1]);
	GLfloat texCoords[] = {
	0, 0,
	0, 1,
	1, 0,
	0, 1,
	1, 0,
	1, 1 };
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), &texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);*/
}


GUI::~GUI()
{
	delete _texture;
}
