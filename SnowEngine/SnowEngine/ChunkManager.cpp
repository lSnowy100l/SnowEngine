#include "ChunkManager.h"

size_t hashFun(Vec3GLui v)
{
	return v.x + v.y + v.z;
}

ChunkManager::ChunkManager(ChunkRenderer* renderer) :
	_renderer(renderer),
	_memory_manager(1 << (3 * CHUNK_CACHE_SIZE_POW)),
	_chunks(hashFun, CHUNK_CACHE_SIZE_POW)
{
	//Checking if the data folder exists, otherwise create it
	if (CreateDirectory(data_directory, NULL) == ERROR_PATH_NOT_FOUND) terror("Could not create/find data folder", -1);

	//Creating random chunks
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			Chunk* c = _memory_manager.requestMemory();
			new (c) Chunk(i, 0, j);
			_chunks.put(c->getPosition(), c);
		}
	}
}

GLubyte ChunkManager::getBlockAt(GLuint x, GLuint y, GLuint z) {
	Chunk* c = getChunk(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE);
	return c == nullptr ? 0 : c->getBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE);
}

void ChunkManager::setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type) {
	Chunk* c;

	c = _chunks.get(Vec3GLui(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE));
	
	if(c != nullptr) c->setBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE, type);
}

void ChunkManager::update() {
 	_renderer->addToRenderList(_chunks.get(Vec3GLui(0, 0, 0)));
}


Chunk* ChunkManager::getChunk(GLuint x, GLuint y, GLuint z)
{
	return _chunks.get(Vec3GLui(x, y, z));
}

ChunkManager::~ChunkManager()
{
}
