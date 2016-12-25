#include "MasterRenderer.h"


ChunkRenderer::ChunkRenderer(MasterRenderer* renderer, const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
	_renderer = renderer;
	_vertexShaderId = genShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	_fragmentShaderId = genShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	getAttribLocations();
	glLinkProgram(_programId);
	getUniformLocations();
	glValidateProgram(_programId);
}

void ChunkRenderer::render() {
	glUseProgram(_programId);
	glUniformMatrix4fv(translationMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getTranslationMatrix().data[0]);
	glUniformMatrix4fv(rotationMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getRotationMatrix().data[0]);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getProjectionMatrix().data[0]);
	while (first_Chunk != nullptr) {
		renderChunk(first_Chunk->chunk);
		// Empty render list
		ChunkNode* aux = first_Chunk;
		first_Chunk = first_Chunk->next;
		delete aux;
	}
	glUseProgram(NULL);
}

void ChunkRenderer::getAttribLocations() {
	glBindAttribLocation(_programId, 0, "position");
}

void ChunkRenderer::getUniformLocations() {
	chunkTranslationMatrixLoc = glGetUniformLocation(_programId, "chunkTranslationMatrix");
	translationMatrixLoc = glGetUniformLocation(_programId, "translationMatrix");
	rotationMatrixLoc = glGetUniformLocation(_programId, "rotationMatrix");
	projectionMatrixLoc = glGetUniformLocation(_programId, "projectionMatrix");
}

void ChunkRenderer::renderChunk(Chunk* chunk) {
	glUniformMatrix4fv(chunkTranslationMatrixLoc, 1, GL_FALSE, &Mat4GLf::translationMatrix(Vec3GLf(chunk->getPosition().x*32, chunk->getPosition().y * 32, chunk->getPosition().z * 32)).data[0]);
	glBindVertexArray(chunk->getVaoId());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, chunk->getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(NULL);
}

void ChunkRenderer::addToRenderList(Chunk * chunk)
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
