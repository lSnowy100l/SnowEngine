#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Chunk.h"

const BlockData Chunk::blockData[] = {
	BlockData(0, 0, 0, 0),
	BlockData(125, 125, 125, 255) };

Chunk::Chunk(GLuint x, GLuint y, GLuint z) : x(x), y(y), z(z)
{
	
	char file_source[MAX_PATH];
	getFileName(file_source);
	blocks = new GLubyte**[CHUNK_SIZE];
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		blocks[x] = new GLubyte*[CHUNK_SIZE];
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			blocks[x][y] = new GLubyte[CHUNK_SIZE];
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
	blocks[x][y][z] = id;
	z = (z + 1) & CHUNK_SIZE_MINUS; // MODULUS
	if (z == 0) {
		y = (y + 1) & CHUNK_SIZE_MINUS;
		if (y == 0) x = (x + 1) & CHUNK_SIZE_MINUS;
	}
	
}

void Chunk::addFace(GLubyte* data, GLfloat* ambientData, GLubyte type, GLubyte x, GLubyte y, GLubyte z, GLint& size, GLint& aoSize) {
	switch (type) {
	case 0:
		data[size++] = x;		data[size++] = y;		data[size++] = z;
		data[size++] = x;		data[size++] = y;		data[size++] = z + 1;
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;

		data[size++] = x;		data[size++] = y;		data[size++] = z;
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z + 1;
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;

		break;
	case 1:
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;

		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		break;
	case 2:
		data[size++] = x;		data[size++] = y;		data[size++] = z + 1;
		data[size++] = x;		data[size++] = y;		data[size++] = z;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;

		data[size++] = x;		data[size++] = y;		data[size++] = z;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		break;
	case 3:
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z;
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;

		data[size++] = x;		data[size++] = y + 1;	data[size++] = z;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		break;
	case 4:
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;

		data[size++] = x;		data[size++] = y + 1;	data[size++] = z;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z;
		data[size++] = x;		data[size++] = y;		data[size++] = z;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		break;
	case 5:
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y + 1;	data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		
		data[size++] = x;		data[size++] = y + 1;	data[size++] = z + 1;
		data[size++] = x;		data[size++] = y;		data[size++] = z + 1;
		data[size++] = x + 1;	data[size++] = y;		data[size++] = z + 1;

		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambientData[aoSize++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		break;
	}
}

void Chunk::update() {
	if (updated) {
		return;
	}

	GLubyte* vertexData = new GLubyte[CHUNK_SIZE_CUBE * 6 * 3 * 3];
	GLfloat* ambientData = new GLfloat[CHUNK_SIZE_CUBE * 6 * 3];
	GLint size = 0, aoSize = 0;
	
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			for (GLubyte z = 0; z < CHUNK_SIZE; z++) {
				if (blocks[x][y][z] == 0) continue;
				if (x == 0 || blocks[x - 1][y][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 0, x, y, z, size, aoSize);
				}
				if (x == CHUNK_SIZE_MINUS || blocks[x + 1][y][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 1, x, y, z, size, aoSize);
				}
				if (y == 0 || blocks[x][y - 1][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 2, x, y, z, size, aoSize);
				}
				if (y == CHUNK_SIZE_MINUS || blocks[x][y + 1][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 3, x, y, z, size, aoSize);
				}
				if (z == 0 || blocks[x][y][z - 1] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 4, x, y, z, size, aoSize);
				}
				if (z == CHUNK_SIZE_MINUS || blocks[x][y][z + 1] == 0) {
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
	updated = true;
}

void Chunk::getFileName(char * file_destination)
{
	file_destination[0] = '\0';
	sprintf(file_destination, "%s%d_%d_%d.chk", data_directory, x, y, z);
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
				blocks[x][y][z] = 1;
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
			delete[] blocks[x][y];
		}
		delete[] blocks[x];
	}
	delete[] blocks;
}
