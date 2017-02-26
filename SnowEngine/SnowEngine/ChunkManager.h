#pragma once

#include "MasterRenderer.h"
#include "MemoryManager.h"
#include "HashMap.h"

#define CHUNK_CACHE_SIZE_POW 3 // 2^3n

class ChunkManager
{
private:
	ChunkRenderer* _renderer;
	HashMap<Vec3GLui, Chunk*> _chunks;
	MemoryManager<Chunk> _memory_manager;
public:
	ChunkManager(ChunkRenderer* renderer);
	void update();
	Chunk* getChunk(GLuint x, GLuint y, GLuint z);
	GLubyte getBlockAt(GLuint x, GLuint y, GLuint z);
	void setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type);
	~ChunkManager();
};

