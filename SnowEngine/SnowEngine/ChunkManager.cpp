#include "ChunkManager.h"


ChunkManager::ChunkManager(ChunkRenderer* renderer) : _renderer(renderer)
{
	//Checking if the data folder exists, otherwise create it
	if (CreateDirectory(data_directory, NULL) == ERROR_PATH_NOT_FOUND) terror("Could not create/find data folder", -1);

	// Create hash table and memory pool
	_memory_pool = new MemoryPool();
	_hash_table = new HashTable();
	_hash_table->attachMemoryPool(_memory_pool);

	//Creating random chunks
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++)
			_hash_table->insertChunk(new Chunk(i, 0, j));
	}
}

GLubyte ChunkManager::getBlockAt(GLuint x, GLuint y, GLuint z) {
	Chunk* c = getChunk(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE);
	return c == nullptr ? 0 : c->getBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE);
}

void ChunkManager::setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type) {
	Chunk* c;

	c = _hash_table->getChunkByKey(Vec3GLui(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE));
	
	if(c != nullptr) c->setBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE, type);
}


void ChunkManager::update() {
	
	Chunk * c;
	Bucket * b;
	for(int i = 0; i < ENTRY_SIZE; i++){
		b = this->_hash_table->getBucketAt(i);
		do {
			if (b != nullptr) {
				c = b->chk;
				c->update();
				_renderer->addToRenderList(c);
				b = b->next;
			}
		} while (b != nullptr);
	}
}


Chunk* ChunkManager::getChunk(GLuint x, GLuint y, GLuint z)
{
	return _hash_table->getChunkByKey(Vec3GLui(x, y, z));
}

ChunkManager::~ChunkManager()
{
	delete this->_memory_pool;
}
