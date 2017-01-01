#pragma once

#include "MasterRenderer.h"

class ChunkManager
{
private:
	ChunkRenderer* _renderer;
	HashTable * ht;
	memory_pool * mp;
public:
	ChunkManager(ChunkRenderer* renderer);
	void update();
	Chunk* getChunk(GLuint x, GLuint y, GLuint z);
	GLubyte getBlockAt(GLuint x, GLuint y, GLuint z);
	HashTable * getAssociatedHashTable() { return ht; }
	void setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type);
	~ChunkManager();
};

