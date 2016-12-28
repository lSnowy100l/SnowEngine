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
	bool isEqualTo(Chunk * chk);
	bool isEqualTo(Vec3GLf * v);
	void update();
	~Chunk();
private:
	void loadFromFile(FILE* ptr);
	void generateChunk();
	void insertBlock(GLubyte & x, GLubyte & y, GLubyte & z, GLubyte id);
	void getFileName(char * file_destination);
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
	uint64_t entry_size;
	memory_pool * mp;

public:
	HashTable(uint64_t entry_size);
	void attachMemoryPool(memory_pool * mp);
	Chunk * getChunkByKey(Vec3GLf key);
	void insertChunk(Chunk * chk);
	~HashTable();

private:
	uint64_t computeHashOf(Vec3GLf key);
};

