#pragma once

#include "Renderer.h"
#include "Vec3GLf.h"
#include "Chunk.h"

class ChunkRenderer;

class MasterRenderer
{
private:
	Vec3GLf _position, _lookAt;
	// All renderers go here
	ChunkRenderer* cr;
public:
	MasterRenderer(const char* CRVSFP, const char* CRFSFP, Vec3GLf position);
	void renderAll();
	inline void setPosition(Vec3GLf position) { _position = position; }
	inline void setLookAt(Vec3GLf lookAt) { _lookAt = lookAt; }
	inline ChunkRenderer* getChunkRenderer() { return cr; }
	~MasterRenderer();
};

struct ChunkNode {
	ChunkNode* next;
	const Chunk* chunk;
};

class ChunkRenderer : public Renderer {
private:
	MasterRenderer* _renderer;
	ChunkNode* first_Chunk;
private:
	void renderChunk(const Chunk * chunk);
public:
	ChunkRenderer(MasterRenderer* renderer, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	void renderAllChunks();
	void bindAtributes();
	void addToRenderList(const Chunk* chunk);
	~ChunkRenderer();
};

