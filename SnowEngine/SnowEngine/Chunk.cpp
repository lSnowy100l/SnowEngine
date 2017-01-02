#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Chunk.h"


const BlockData Chunk::blockData[] = {
	BlockData(0, 0, 0, 0),
	BlockData(125, 125, 125, 255) };

Chunk::Chunk(Vec3GLui position) : _position(position) {
	char file_source[MAX_PATH];
	getFileName(file_source);
	_blocks = new GLubyte**[CHUNK_SIZE];
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		_blocks[x] = new GLubyte*[CHUNK_SIZE];
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			_blocks[x][y] = new GLubyte[CHUNK_SIZE];
		}
	}

	FILE * ptr = fopen(file_source, "rb");
	if (ptr == nullptr)
		generateChunk();
	else
		loadFromFile(ptr);

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(VBO_COUNT, &_vboId[0]);
	update();
}

void Chunk::insertBlock(GLubyte& x, GLubyte& y, GLubyte& z, GLubyte id) {
	_blocks[x][y][z] = id;
	z = (z + 1) & CHUNK_SIZE_MINUS; // MODULUS
	if (z == 0) {
		y = (y + 1) & CHUNK_SIZE_MINUS;
		if (y == 0) x = (x + 1) & CHUNK_SIZE_MINUS;
	}
}

void Chunk::addFace(GLubyte* vertex_data, GLfloat* ambient_data, GLubyte face_type, GLubyte x, GLubyte y, GLubyte z, GLint& size, GLint& ao_size)
{
	switch (face_type) {
	case 0:
		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z + 1;
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;

		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;

		break;
	case 1:
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;

		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		break;
	case 2:
		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z + 1;
		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;

		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		break;
	case 3:
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z;
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;

		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		break;
	case 4:
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;

		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z;
		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		break;
	case 5:
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		
		vertex_data[size++] = x;		vertex_data[size++] = y + 1;	vertex_data[size++] = z + 1;
		vertex_data[size++] = x;		vertex_data[size++] = y;		vertex_data[size++] = z + 1;
		vertex_data[size++] = x + 1;	vertex_data[size++] = y;		vertex_data[size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		break;
	}
}

void Chunk::update() {
	// If the chunk is already up to date don't do anything
	if (_updated) {
		return;
	}

	GLubyte* vertexData = new GLubyte[CHUNK_SIZE_CUBE * 6 * 3 * 3];
	GLfloat* ambientData = new GLfloat[CHUNK_SIZE_CUBE * 6 * 3];
	GLint size = 0, aoSize = 0;
	
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			for (GLubyte z = 0; z < CHUNK_SIZE; z++) {
				if (_blocks[x][y][z] == 0) continue;
				if (x == 0 || _blocks[x - 1][y][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 0, x, y, z, size, aoSize);
				}
				if (x == CHUNK_SIZE_MINUS || _blocks[x + 1][y][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 1, x, y, z, size, aoSize);
				}
				if (y == 0 || _blocks[x][y - 1][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 2, x, y, z, size, aoSize);
				}
				if (y == CHUNK_SIZE_MINUS || _blocks[x][y + 1][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 3, x, y, z, size, aoSize);
				}
				if (z == 0 || _blocks[x][y][z - 1] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 4, x, y, z, size, aoSize);
				}
				if (z == CHUNK_SIZE_MINUS || _blocks[x][y][z + 1] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 5, x, y, z, size, aoSize);
				}
			}
		}
	}
	
	_vertexCount = size / 3;

	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLubyte), vertexData, GL_DYNAMIC_DRAW);
	glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, aoSize * sizeof(GLfloat), ambientData, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	delete[] vertexData;
	delete[] ambientData;
	_updated = true;
}

void Chunk::getFileName(char * file_destination)
{
	file_destination[0] = '\0';
	sprintf(file_destination, "%s%d_%d_%d.chk", data_directory, _position.x, _position.y, _position.z);
}

void Chunk::loadFromFile(FILE* ptr) {
	FileChunkNode buffer;
	
	GLubyte x = 0, y = 0, z = 0;

	// Moves the execution to the empty tag in order to fill the chunk with air if the file is empty
	if(fread(&buffer, sizeof(FileChunkNode), 1, ptr) == 0) goto empty;
	
	do {
		for (int a = 0; a < buffer.amount; a++)
			insertBlock(x, y, z, buffer.block_id);
		fread(&buffer, sizeof(FileChunkNode), 1, ptr);
	} while (!feof(ptr));
	fclose(ptr);

	// Fills the chunk with air until every position is initialized
	while (x != 0 || y != 0 || z != 0)
	empty:	insertBlock(x, y, z, 0);
}

void Chunk::generateChunk() {
	_blocks = new GLubyte**[CHUNK_SIZE];
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		_blocks[x] = new GLubyte*[CHUNK_SIZE];
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			_blocks[x][y] = new GLubyte[CHUNK_SIZE];
			for (GLubyte z = 0; z < CHUNK_SIZE; z++) {
				_blocks[x][y][z] = 1;
			}
		}
	}
}

void Chunk::saveToFile()
{
	std::vector<FileChunkNode> buffers;

	GLubyte amount = 0, last_id = 0;
	FileChunkNode fcn;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				GLubyte actual = _blocks[x][y][z];
				if (actual != last_id || amount == 255) {
					fcn.amount = amount;
					fcn.block_id = last_id;
					if(amount != 0) buffers.push_back(fcn);
					last_id = actual;
					amount = 1;
				}
				else amount++;
				
			}
		}
	}

	fcn.amount = amount;
	fcn.block_id = last_id;
	buffers.push_back(fcn);
	char file_pointer[MAX_PATH];
	getFileName(file_pointer);
	FILE * ptr = fopen(file_pointer, "wb");

	for (FileChunkNode buffer : buffers)
		fwrite(&buffer, sizeof(FileChunkNode), 1, ptr);

	fclose(ptr); 
}

Chunk::~Chunk()
{
	saveToFile();
	glDeleteVertexArrays(1, &_vaoId);
	for (GLushort x = 0; x < CHUNK_SIZE; x++) {
		for (GLushort y = 0; y < CHUNK_SIZE; y++) {
			delete[] _blocks[x][y];
		}
		delete[] _blocks[x];
	}
	delete[] _blocks;
}



HashTable::HashTable()
{
	_hash_table = new hashtable[ENTRY_SIZE];
	if (_hash_table == nullptr) terror("Could not allocate hash table", -1);
	for (int i = 0; i < ENTRY_SIZE; i++) {
		_hash_table[i].bucket_ptr = nullptr;
	}
}

void HashTable::attachMemoryPool(MemoryPool * _memory_pool)
{
	this->_memory_pool = _memory_pool;
}

Bucket * HashTable::getBucketAt(uint64_t index)
{
	return this->_hash_table[index].bucket_ptr;
}

Chunk * HashTable::getChunkByKey(const Vec3GLui& key)
{
	uint64_t hash = this->hashCode(key);
	Bucket * ptr = this->getBucketAt(hash);

	while (ptr != nullptr) {
		if (ptr->chk != nullptr && ptr->chk->getPosition() == key) return ptr->chk;
		ptr = ptr->next;
	}
	return nullptr;
}


void HashTable::insertChunk(Chunk * chk)
{

	uint64_t hash = this->hashCode(chk->getPosition());

	Bucket * b = (Bucket *) this->_memory_pool->requestBytes((uint64_t) sizeof(Bucket));


	b->chk = chk;
	b->next = nullptr;

	if (this->_hash_table[hash].bucket_ptr != nullptr) {
		b->next = this->_hash_table[hash].bucket_ptr;
	}
	this->_hash_table[hash].bucket_ptr = b;
	
}

HashTable::~HashTable()
{
}

uint64_t HashTable::hashCode(Vec3GLui key)
{
	return (((uint64_t) key.x % MODULUS) + ((uint64_t) key.y % MODULUS)*MODULUS + ((uint64_t) key.z % MODULUS)*MODULUS*MODULUS);
}

MemoryPool::MemoryPool()
{
	this->current_pool = 0;
	this->mem_pool = (char **) malloc(MAX_MEM_POOLS * sizeof(char *));
	this->base = (uint64_t *) malloc(MAX_MEM_POOLS * sizeof(uint64_t));
	this->base[0] = 0;
	if (this->mem_pool == nullptr) terror("Could not allocate memory pools", -1);
	this->mem_pool[0] = (char *)malloc(POOL_SIZE * sizeof(char));
	if (this->mem_pool[0] == nullptr) terror("Could not allocate initial memory pool", -1);
}

void * MemoryPool::requestBytes(uint64_t n_bytes)
{
	void * ptr;
	if (this->base[this->current_pool] + n_bytes >= POOL_SIZE) {
		this->current_pool++;
		this->mem_pool[this->current_pool] = (char *)malloc(POOL_SIZE * sizeof(char));
		if (this->mem_pool[this->current_pool] == nullptr) terror("Could not allocate memory pool", -1);
		this->base[this->current_pool] = 0;
	}
	
	ptr = &this->mem_pool[this->current_pool][0] + this->base[this->current_pool];
	this->base[this->current_pool] = this->base[this->current_pool] + n_bytes;
	
	return ptr;
}

MemoryPool::~MemoryPool()
{
	for (int i = 0; i <= this->current_pool; i++) {
		free(this->mem_pool[i]);
	}
	free(this->mem_pool);
	free(this->base);
}
