#pragma once

#include <GL/glew.h>
#include <vector>
#include <sstream>
#include "Vec3GLf.h"

#define CHUNK_POW 5
#define CHUNK_FOLDER "chunk_data/"

struct FileChunkNode {
	GLubyte block_id;
	GLubyte amount;
};

class Chunk
{
public:
	static const GLubyte CHUNK_SIZE = 1 << CHUNK_POW;
	static const GLubyte CHUNK_SIZE_MINUS = CHUNK_SIZE - 1;
	static const GLuint CHUNK_SIZE_CUBE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
private:
	GLubyte*** blocks;
	GLuint x, y, z;
	GLuint _vaoId, _vboId, _vertexCount;
public:
	Chunk(GLuint x, GLuint y, GLuint z);
	inline Vec3GLf getPosition() { return Vec3GLf(x, y, z); }
	inline GLbyte getBlock(GLubyte x, GLubyte y, GLubyte z) { return blocks[x][y][z]; }
	void saveToFile();
	inline void setBlock(GLubyte x, GLubyte y, GLubyte z, GLubyte id) { blocks[x][y][z] = id; }
	inline GLuint getVaoId() { return _vaoId; }
	inline GLuint getVertexCount() { return _vertexCount; }
	~Chunk();
private:
	void loadFromFile(FILE* ptr);
	void generateChunk();
	void insertBlock(GLubyte & x, GLubyte & y, GLubyte & z, GLubyte id);
	std::string getFileName();
};

