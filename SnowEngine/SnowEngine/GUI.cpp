#include "GUI.h"



GUI::GUI() {
	_texture = new Texture("test.bmp");

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(2, &_vboId[0]);
	glBindVertexArray(_vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	GLfloat data[] = { 0, 500, 0, 0, 500, 500, 500, 0 };
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[1]);
	GLfloat texCoords[] = { 0, 1, 0, 0, 1, 1, 1, 0 };
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), &texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}


GUI::~GUI()
{
	delete _texture;
}
