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
	glUniformMatrix4fv(rotationMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getRotationMatrix().data[0]);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &_renderer->getCamera()->getProjectionMatrix().data[0]);
	/*while (first_Chunk != nullptr) {
		renderChunk(first_Chunk->chunk);
		// Empty render list
		ChunkNode* aux = first_Chunk;
		first_Chunk = first_Chunk->next;
		delete aux;
	}*/
	// CODE TO RENDER A SIMPLE CUBE JUST FOR TESTING PURPOSES
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triángulo 1 : comienza
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triángulo 1 : termina
		1.0f, 1.0f,-1.0f, // triángulo 2 : comienza
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triángulo 2 : termina
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	static const GLfloat g_vertex_buffer_data2[] = {
		0.5, 0.5, 0.0,
		-0.5, 0.5, 0.0,
		-0.5, -0.5, 0.0,

		0.5, 0.5, 0.0,
		0.5, -0.5, 0.0,
		-0.5, -0.5, 0.0
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, g_vertex_buffer_data);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);
	glUseProgram(NULL);
}

void ChunkRenderer::bindAtributes() {
	//glBindAttribLocation(_programId, 0, "position");
	translationMatrixLoc = glGetUniformLocation(_programId, "translationMatrix");
	rotationMatrixLoc = glGetUniformLocation(_programId, "rotationMatrix");
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
