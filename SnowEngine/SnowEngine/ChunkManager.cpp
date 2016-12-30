#include "ChunkManager.h"


ChunkManager::ChunkManager(ChunkRenderer* renderer) : _renderer(renderer)
{
	//Checking if the data folder exists, otherwise create it
	if (CreateDirectory(data_directory, NULL) == ERROR_PATH_NOT_FOUND) terror("Could not create/find data folder", -1);

	// Create hash table and memory pool
	mp = new memory_pool();
	ht = new HashTable();
	ht->attachMemoryPool(mp);

	//Creating random chunks
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++)
			ht->insertChunk(new Chunk(i, 0, j));
	}

	ht->insertChunk(new Chunk(4, 1, 4));
	ht->insertChunk(new Chunk(4, 2, 4));
	ht->insertChunk(new Chunk(4, 3, 4));
}

GLubyte ChunkManager::getBlockAt(GLuint x, GLuint y, GLuint z) {
	Chunk* c = getChunk(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE);
	return c == nullptr ? NULL : c->getBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE);
}

void ChunkManager::setBlockAt(GLuint x, GLuint y, GLuint z, GLubyte type) {
	Chunk* c;

	c = ht->getChunkByKey(Vec3GLf(x / Chunk::CHUNK_SIZE, y / Chunk::CHUNK_SIZE, z / Chunk::CHUNK_SIZE));
	
	if(c != nullptr) c->setBlock(x % Chunk::CHUNK_SIZE, y % Chunk::CHUNK_SIZE, z % Chunk::CHUNK_SIZE, type);
}


void ChunkManager::update() {
	
	Chunk * c;
	Bucket * b;
	for(int i=0; i<ENTRY_SIZE; i++){
		b = this->ht->getBucketAt(i);
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


Chunk* ChunkManager::getChunk(GLuint x, GLuint y, GLuint z) {

	return ht->getChunkByKey(Vec3GLf(x, y, z));
}

ChunkManager::~ChunkManager()
{
	delete this->mp;
}
