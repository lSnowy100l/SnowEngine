#include "ChunkRenderer.h"



ChunkRenderer::ChunkRenderer()
{
}

void ChunkRenderer::renderAllChunks() {
	// Context preparation etc.
	while (first_Chunk != nullptr) {
		renderChunk(first_Chunk->chunk);
	}
}

void ChunkRenderer::renderChunk(const Chunk* chunk) {
	//TODO
}

void ChunkRenderer::addToRenderList(const Chunk * chunk)
{
	ChunkNode* cn = new ChunkNode;
	cn->chunk = chunk;
	cn->next = first_Chunk;
	first_Chunk = cn;
}

ChunkRenderer::~ChunkRenderer()
{
}
