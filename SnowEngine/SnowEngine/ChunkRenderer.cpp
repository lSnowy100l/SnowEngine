#include "MasterRenderer.h"


ChunkRenderer::ChunkRenderer(MasterRenderer* renderer, const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
	_renderer = renderer;
	_vertexShaderId = genShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	_fragmentShaderId = genShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);
	glLinkProgram(_programId);
	bindAtributes();
	glValidateProgram(_programId);
}

void ChunkRenderer::render() {
	glUseProgram(_programId);
	glUniformMatrix4fv(translationMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getTranslationMatrix().data[0]);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getProjectionMatrix().data[0]);
	/*while (first_Chunk != nullptr) {
		renderChunk(first_Chunk->chunk);
		// Empty render list
		ChunkNode* aux = first_Chunk;
		first_Chunk = first_Chunk->next;
		delete aux;
	}*/
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(-0.5, -0.5, 0);
	glVertex3f(0.5, -0.5, 0);

	glVertex3f(-0.5, 0.5, 0);
	
	glVertex3f(-0.5, -0.5, 0);
	glVertex3f(0.5, 0.5, 0);
	glEnd();
	glUseProgram(NULL);
}

void ChunkRenderer::bindAtributes() {
	//glBindAttribLocation(_programId, 0, "position");
	translationMatrixLoc = glGetUniformLocation(_programId, "translationMatrix");
	projectionMatrixLoc = glGetUniformLocation(_programId, "projectionMatrix");
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
