#pragma once

#include "Chunk.h"

struct ChunkNode {
	ChunkNode* next;
	const Chunk* chunk;
};

class ChunkRenderer
{
private:
	ChunkNode* first_Chunk;
private:
	void renderChunk(const Chunk * chunk);
public:
	ChunkRenderer();
	void renderAllChunks();
	void addToRenderList(const Chunk* chunk);
	~ChunkRenderer();
};

