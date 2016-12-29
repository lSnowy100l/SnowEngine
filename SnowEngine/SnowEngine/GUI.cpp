#include "GUI.h"



GUI::GUI()
{
	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &_vboId);
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	GLfloat data[] = { -0.1f, 0.1f, -0.1f, -0.1f, 0.1f, 0.1f, 0.1f, -0.1f };
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}


GUI::~GUI()
{
}
