#pragma once

#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "Utils.h"

#define BLOCK_COUNT 2
#define CHUNK_POW 5
#define MAX_MEM_POOLS 256
#define POOL_SIZE 1024*1024*256
#define MODULUS 8
#define ENTRY_SIZE (MODULUS*MODULUS*MODULUS)
#define CHUNK_FOLDER "chunk_data/"
#define VBO_COUNT 2
#define OFFSET_BLOCK 0.5 //The offset to the center of a block
#define SIZE_BLOCK 0.25

struct FileChunkNode {
	GLubyte block_id;
	GLubyte amount;
};

struct BlockData {
	BlockData(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : _red(r), _green(g), _blue(b), _alpha(a) {}
	GLubyte _red, _green, _blue, _alpha;
};

struct FaceData {
	GLbitfield xpos : 1;
	GLbitfield xneg : 1;
	GLbitfield ypos : 1;
	GLbitfield yneg : 1;
	GLbitfield zpos : 1;
	GLbitfield zneg : 1;
};


class Chunk
{
public:
	static const GLubyte CHUNK_SIZE = 1 << CHUNK_POW;
	static const GLubyte CHUNK_SIZE_MINUS = CHUNK_SIZE - 1;
	static const GLuint CHUNK_SIZE_CUBE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
	static const BlockData blockData[2];

	static GLubyte* vertexData;
	static GLfloat* ambientData;

private:
	GLubyte _blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	Vec3GLui _position;
	GLuint _vaoId, _vboId[VBO_COUNT], _vertexCount;
	bool _updated = false;

public:
	inline Chunk(GLuint x, GLuint y, GLuint z) : Chunk(Vec3GLui(x, y, z)) {}
	Chunk(Vec3GLui position);
	inline Vec3GLui getPosition() { return _position; }
	inline GLubyte getBlock(GLubyte x, GLubyte y, GLubyte z) { return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE ? _blocks[x][y][z] : 0; }
	void saveToFile();
	inline bool setBlock(GLubyte x, GLubyte y, GLubyte z, GLubyte id) { if (_blocks[x][y][z] != id) { _blocks[x][y][z] = id; _updated = false; } return _updated; }
	inline GLuint getVaoId() { return _vaoId; }
	inline GLuint getVertexCount() { return _vertexCount; }
	void update();
	~Chunk();
	inline bool operator==(const Chunk* c) { return _position == c->_position; }

private:
	void loadFromFile(FILE* ptr);
	void generateChunk();
	void insertBlock(GLubyte & x, GLubyte & y, GLubyte & z, GLubyte id);
	void getFileName(char * file_destination);
	void addFace(GLubyte* data, GLfloat* ambient_data, GLubyte type, GLubyte x, GLubyte y, GLubyte z, GLint& _size, GLint& aoSize);
};