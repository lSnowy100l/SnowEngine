#include "Chunk.h"



Chunk::Chunk(GLuint x, GLuint y, GLuint z) : x(x), y(y), z(z)
{
	blocks = new GLubyte**[CHUNK_SIZE];
	for (GLushort i = 0; i < CHUNK_SIZE; i++) {
		for (GLushort j = 0; j < CHUNK_SIZE; j++) {

		}
	}
}


Chunk::~Chunk()
{
}
