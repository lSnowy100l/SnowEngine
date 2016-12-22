#include "Chunk.h"



Chunk::Chunk(GLuint x, GLuint y, GLuint z) : x(x), y(y), z(z)
{
	blocks = new GLubyte**[CHUNK_SIZE];
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		blocks[x] = new GLubyte*[CHUNK_SIZE];
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			blocks[x][y] = new GLubyte[CHUNK_SIZE];
		}
	}

	FILE * ptr = fopen(&getFileName()[0], "rb");
	if (ptr == nullptr)
		generateChunk();
	else
		loadFromFile(ptr);
}

void Chunk::insertBlock(GLubyte& x, GLubyte& y, GLubyte& z, GLubyte id) {
	blocks[x][y][z] = id;
	z = (z + 1) & CHUNK_SIZE_MINUS; // MODULUS
	if (z == 0) {
		y = (y + 1) & CHUNK_SIZE_MINUS;
		if (y == 0) x = (x + 1) & CHUNK_SIZE_MINUS;
	}
	
}

std::string Chunk::getFileName()
{
	std::stringstream ss;
	ss << "./" << CHUNK_FOLDER << x << "_" << y << "_" << z << ".chunk";
	return ss.str();
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
	blocks = new GLubyte**[CHUNK_SIZE];
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		blocks[x] = new GLubyte*[CHUNK_SIZE];
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			blocks[x][y] = new GLubyte[CHUNK_SIZE];
			for (GLubyte z = 0; z < CHUNK_SIZE; z++) {
				blocks[x][y][z] = y < 20 ? 'A' : 'B';
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
				GLubyte actual = blocks[x][y][z];
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
	FILE * ptr = fopen(&getFileName()[0], "wb");

	for (FileChunkNode buffer : buffers)
		fwrite(&buffer, sizeof(FileChunkNode), 1, ptr);

	fclose(ptr);
}

Chunk::~Chunk()
{
	for (GLushort x = 0; x < CHUNK_SIZE; x++) {
		for (GLushort y = 0; y < CHUNK_SIZE; y++) {
			delete[] blocks[x][y];
		}
		delete[] blocks[x];
	}
	delete[] blocks;
}
