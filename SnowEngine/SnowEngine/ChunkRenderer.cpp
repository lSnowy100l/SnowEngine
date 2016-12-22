#include "MasterRenderer.h"


ChunkRenderer::ChunkRenderer(MasterRenderer* renderer, const char * vertexShaderFilePath, const char * fragmentShaderFilePath) : _renderer(renderer) {
	_vertexShaderId = genShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	_fragmentShaderId = genShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glLinkProgram(_programId);
	glValidateProgram(_programId);
}

void ChunkRenderer::renderAllChunks() {
	glUseProgram(_programId);
	while (first_Chunk != nullptr) {
		renderChunk(first_Chunk->chunk);
		// Empty render list
		ChunkNode* aux = first_Chunk;
		first_Chunk = first_Chunk->next;
		delete aux;
	}
	glUseProgram(NULL);
}

void ChunkRenderer::bindAtributes() {

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
	clear();
}
