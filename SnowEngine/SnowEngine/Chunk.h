#pragma once

#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "Vec3GLf.h"

#define BLOCK_COUNT 2
#define CHUNK_POW 5
#define CHUNK_FOLDER "chunk_data/"

struct FileChunkNode {
	GLubyte block_id;
	GLubyte amount;
};

struct BlockData {
	BlockData(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : _red(r), _green(g), _blue(b), _alpha(a) {}
	GLubyte _red, _green, _blue, _alpha;
};



class Chunk
{
public:
	static const GLubyte CHUNK_SIZE = 1 << CHUNK_POW;
	static const GLubyte CHUNK_SIZE_MINUS = CHUNK_SIZE - 1;
	static const GLuint CHUNK_SIZE_CUBE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
	static const BlockData blockData[2];
private:
	GLubyte*** blocks;
	GLuint x, y, z;
	GLuint _vaoId, _vboId, _vertexCount;
	bool updated = false;
public:
	Chunk(GLuint x, GLuint y, GLuint z);
	inline Vec3GLf getPosition() { return Vec3GLf(x, y, z); }
	inline GLubyte getBlock(GLubyte x, GLubyte y, GLubyte z) { return blocks[x][y][z]; }
	void saveToFile();
	inline bool setBlock(GLubyte x, GLubyte y, GLubyte z, GLubyte id) { if (blocks[x][y][z] != id) { blocks[x][y][z] = id; updated = false; return updated; } }
	inline GLuint getVaoId() { return _vaoId; }
	inline GLuint getVertexCount() { return _vertexCount; }
	void update();
	~Chunk();
private:
	void loadFromFile(FILE* ptr);
	void generateChunk();
	void insertBlock(GLubyte & x, GLubyte & y, GLubyte & z, GLubyte id);
	std::string getFileName();
};

