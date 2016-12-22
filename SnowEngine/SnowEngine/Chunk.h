#pragma once

#include <GL/glew.h>
#include <vector>
#include <sstream>

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
private:
	GLubyte*** blocks;
	GLuint x, y, z;
public:
	Chunk(GLuint x, GLuint y, GLuint z);
	inline GLbyte getBlock(GLubyte x, GLubyte y, GLubyte z) { return blocks[x][y][z]; }
	void saveToFile();
	inline void setBlock(GLubyte x, GLubyte y, GLubyte z, GLubyte id) { blocks[x][y][z] = id; }
	~Chunk();
private:
	void loadFromFile(FILE* ptr);
	void generateChunk();
	void insertBlock(GLubyte & x, GLubyte & y, GLubyte & z, GLubyte id);
	std::string getFileName();
};

