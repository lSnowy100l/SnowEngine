#include "MasterRenderer.h"


ChunkRenderer::ChunkRenderer(MasterRenderer* renderer, const char * vertexShaderFilePath, const char * fragmentShaderFilePath) {
	_renderer = renderer;
	_vertex_shader_id = genShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	_fragment_shader_id = genShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
	_program_id = glCreateProgram();
	glAttachShader(_program_id, _vertex_shader_id);
	glAttachShader(_program_id, _fragment_shader_id);
	getAttribLocations();
	glLinkProgram(_program_id);
	getUniformLocations();
	glValidateProgram(_program_id);
}

void ChunkRenderer::render() {
	glUseProgram(_program_id);
	glUniformMatrix4fv(_translation_matrix_loc, 1, GL_FALSE, &_renderer->getCamera()->getTranslationMatrix().data[0]);
	glUniformMatrix4fv(_rotation_matrix_loc, 1, GL_FALSE, &_renderer->getCamera()->getRotationMatrix().data[0]);
	glUniformMatrix4fv(_projection_matrix_loc, 1, GL_FALSE, &_renderer->getCamera()->getProjectionMatrix().data[0]);
	LinkedIterator<Chunk*> lit = chunk_list.linked_iterator();
	while (lit.hasNext())
		renderChunk(lit.next());
	chunk_list.empty();
	glUseProgram(NULL);
}

void ChunkRenderer::getAttribLocations()
{
	glBindAttribLocation(_program_id, 0, "position");
	glBindAttribLocation(_program_id, 1, "ambientOcclusion");
}

void ChunkRenderer::getUniformLocations()
{
	_chunk_translation_matrix_loc = glGetUniformLocation(_program_id, "chunkTranslationMatrix");
	_translation_matrix_loc =		glGetUniformLocation(_program_id, "translationMatrix");
	_rotation_matrix_loc =			glGetUniformLocation(_program_id, "rotationMatrix");
	_projection_matrix_loc =		glGetUniformLocation(_program_id, "projectionMatrix");
}

void ChunkRenderer::renderChunk(Chunk* chunk)
{
	glUniformMatrix4fv(_chunk_translation_matrix_loc, 1, GL_FALSE, &Mat4GLf::translationMatrix(Vec3GLf(chunk->getPosition().x*32, chunk->getPosition().y * 32, chunk->getPosition().z * 32)).data[0]);
	glBindVertexArray(chunk->getVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, chunk->getVertexCount());
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(NULL);
}

void ChunkRenderer::addToRenderList(Chunk * chunk)
{
	chunk_list.add(chunk);
}

ChunkRenderer::~ChunkRenderer()
{
	clear();
}
