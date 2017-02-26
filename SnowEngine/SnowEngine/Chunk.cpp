#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Chunk.h"

GLubyte* Chunk::vertexData = new GLubyte[CHUNK_SIZE_CUBE * 6 * 3 * 3];
GLfloat* Chunk::ambientData = new GLfloat[CHUNK_SIZE_CUBE * 6 * 3];

const BlockData Chunk::blockData[] = {
	BlockData(0, 0, 0, 0),
	BlockData(125, 125, 125, 255) };

Chunk::Chunk(Vec3GLui position) : _position(position) {
	char file_source[MAX_PATH];
	getFileName(file_source);

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

void Chunk::addFace(GLubyte* vertex_data, GLfloat* ambient_data, GLubyte face_type, GLubyte x, GLubyte y, GLubyte z, GLint& _size, GLint& ao_size)
{
	switch (face_type) {
	case 0:
		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;

		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;

		break;
	case 1:
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;

		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		break;
	case 2:
		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;

		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y - 1, z) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		break;
	case 3:
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;

		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y + 1, z) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		break;
	case 4:
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;

		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z;
		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y + 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z - 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z - 1) == 0) + (GLfloat)(getBlock(x, y - 1, z - 1) == 0) + (GLfloat)(getBlock(x - 1, y - 1, z - 1) == 0)) / 3;
		break;
	case 5:
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;

		ambient_data[ao_size++] = ((GLfloat)(getBlock(x - 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x - 1, y + 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y - 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y - 1, z + 1) == 0)) / 3;
		ambient_data[ao_size++] = ((GLfloat)(getBlock(x + 1, y, z + 1) == 0) + (GLfloat)(getBlock(x, y + 1, z + 1) == 0) + (GLfloat)(getBlock(x + 1, y + 1, z + 1) == 0)) / 3;
		
		vertex_data[_size++] = x;		vertex_data[_size++] = y + 1;	vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x;		vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;
		vertex_data[_size++] = x + 1;	vertex_data[_size++] = y;		vertex_data[_size++] = z + 1;

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

	GLint _size = 0, aoSize = 0;
	
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
			for (GLubyte z = 0; z < CHUNK_SIZE; z++) {
				if (_blocks[x][y][z] == 0) continue;
				if (x == 0 || _blocks[x - 1][y][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 0, x, y, z, _size, aoSize);
				}
				if (x == CHUNK_SIZE_MINUS || _blocks[x + 1][y][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 1, x, y, z, _size, aoSize);
				}
				if (y == 0 || _blocks[x][y - 1][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 2, x, y, z, _size, aoSize);
				}
				if (y == CHUNK_SIZE_MINUS || _blocks[x][y + 1][z] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 3, x, y, z, _size, aoSize);
				}
				if (z == 0 || _blocks[x][y][z - 1] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 4, x, y, z, _size, aoSize);
				}
				if (z == CHUNK_SIZE_MINUS || _blocks[x][y][z + 1] == 0) {
					//_faceData[x][y][z].ypos = 1;
					addFace(vertexData, ambientData, 5, x, y, z, _size, aoSize);
				}
			}
		}
	}
	
	_vertexCount = _size / 3;

	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, _size * sizeof(GLubyte), vertexData, GL_DYNAMIC_DRAW);
	glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, aoSize * sizeof(GLfloat), ambientData, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
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
	for (GLubyte x = 0; x < CHUNK_SIZE; x++) {
		for (GLubyte y = 0; y < CHUNK_SIZE; y++) {
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
}