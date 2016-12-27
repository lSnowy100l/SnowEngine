#include "ChunkManager.h"


ChunkManager::ChunkManager(ChunkRenderer* renderer) : _renderer(renderer)
{
	//Checking if the data folder exists, otherwise create it
	if (CreateDirectory(data_directory, NULL) == ERROR_PATH_NOT_FOUND) terror("Could not create/find data folder", -1);


	//Creating random chunks
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			_chunks.push_back(new Chunk(i, 0, j));
	}
}

GLubyte ChunkManager::getBlockAt(GLuint x, GLuint y, GLuint z) {
	Chunk* c = getChunk(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE);
	return c == nullptr ? NULL : c->getBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE);
}

void ChunkManager::setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type) {
	Chunk* c;
	if (last_access != nullptr && Vec3GLf(x, y, z) == last_access->getPosition()) c = last_access;
	else {
		c = getChunk(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE);
		if (c != nullptr) last_access = c;
	}
	
	if (c != nullptr) {
		c->setBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE, type);
	}
}


void ChunkManager::update() {
	
	for (Chunk* c : _chunks) {
		c->update();
		_renderer->addToRenderList(c);
	}
}

Chunk* ChunkManager::getChunk(GLuint x, GLuint y, GLuint z) {
	bool found = false;
	size_t i = 0;
	
	while (!found && i < _chunks.size()) {
		found = _chunks[i]->getPosition() == Vec3GLf(x, y, z);
		if (!found) i++;
	}
	

	return found ? _chunks[i] : nullptr;
}

ChunkManager::~ChunkManager()
{
	for (Chunk* c : _chunks)
		delete c;
}
