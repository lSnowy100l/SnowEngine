#pragma once

#include "MasterRenderer.h"

class ChunkManager
{
private:
	ChunkRenderer* _renderer;
	HashTable* _hash_table;
	MemoryPool* _memory_pool;
public:
	ChunkManager(ChunkRenderer* renderer);
	void update();
	Chunk* getChunk(GLuint x, GLuint y, GLuint z);
	GLubyte getBlockAt(GLuint x, GLuint y, GLuint z);
	HashTable* getAssociatedHashTable() { return _hash_table; }
	void setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type);
	~ChunkManager();
};

