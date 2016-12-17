#pragma once

#include <GL/glew.h>

class Chunk
{
public:
	static const GLubyte CHUNK_POW = 5;
	static const GLushort CHUNK_SIZE = 1 << CHUNK_POW;
	static const GLushort CHUNK_SIZE_SQUARE = CHUNK_SIZE * CHUNK_SIZE;
	static const GLushort CHUNK_SIZE_CUBE = CHUNK_SIZE_SQUARE * CHUNK_SIZE;
private:
	GLubyte*** blocks;
	GLuint x, y, z;
public:
	Chunk(GLuint x, GLuint y, GLuint z);
	inline GLushort toIndex(int x, int y, int z) { return 0 | x | y << CHUNK_POW | z << CHUNK_SIZE_SQUARE; }
	inline GLbyte getBlock(GLubyte x, GLubyte y, GLubyte z) { return blocks[toIndex(x, y, z)]; }
	~Chunk();
};

