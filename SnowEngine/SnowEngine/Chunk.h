#pragma once

#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <inttypes.h>
#include "Vec3GLf.h"
#include "common.h"

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
private:
	GLubyte*** blocks;
	GLuint x, y, z;
	GLuint _vaoId, _vboId[VBO_COUNT], _vertexCount;
	FaceData*** _faceData;
	bool updated = false;
public:
	Chunk(GLuint x, GLuint y, GLuint z);
	inline Vec3GLf getPosition() { return Vec3GLf(x, y, z); }
	inline GLubyte getBlock(GLubyte x, GLubyte y, GLubyte z) { return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE ? blocks[x][y][z] : 0; }
	void saveToFile();
	inline bool setBlock(GLubyte x, GLubyte y, GLubyte z, GLubyte id) { if (blocks[x][y][z] != id) { blocks[x][y][z] = id; updated = false; return updated; } }
	inline GLuint getVaoId() { return _vaoId; }
	inline GLuint getVertexCount() { return _vertexCount; }
	bool isEqualTo(Chunk * chk);
	bool isEqualTo(Vec3GLf * v);
	void update();
	~Chunk();
private:
	void loadFromFile(FILE* ptr);
	void generateChunk();
	void insertBlock(GLubyte & x, GLubyte & y, GLubyte & z, GLubyte id);
	void getFileName(char * file_destination);
	void addFace(GLubyte* data, GLfloat* ambientData, GLubyte type, GLubyte x, GLubyte y, GLubyte z, GLint& size, GLint& aoSize);
};

class memory_pool {

private:
	//TODO add stack of recently free'd positions
	char ** mem_pool;
	uint64_t * base;
	uint64_t current_pool;
public:
	memory_pool();
	void * request_bytes(uint64_t n_bytes);
	void showWhatYouGot(int k);
	~memory_pool();
};

typedef struct bucket {
	Chunk * chk;
	struct bucket * next;
} Bucket;

struct hashtable {
	Bucket * bucket_ptr;
};

class HashTable
{

private:
	struct hashtable * ht; // struct hashtable ht[size_entry]
	memory_pool * mp;

public:
	HashTable();
	void attachMemoryPool(memory_pool * mp);
	Bucket * getBucketAt(int index); //SOLO PARA SUSTITUIR un ITERADOR POR KEYS
	Chunk * getChunkByKey(Vec3GLf key);
	void insertChunk(Chunk * chk);
	~HashTable();

private:
	uint64_t computeHashOf(Vec3GLf key);
};

