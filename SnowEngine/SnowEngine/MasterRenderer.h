#pragma once

#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Utils.h"
#include "Chunk.h"
#include "Camera.h"

class Renderer;

class MasterRenderer
{
private:
	Camera * _camera;
	std::vector<Renderer*> _renderer_list;
	double _s = 0, _a = 0;
public:
	MasterRenderer(Camera* camera);
	void renderAll();
	void addRenderer(Renderer* renderer) { _renderer_list.push_back(renderer); }
	inline double getFps() { return 1 / (_a - _s); }
	inline Camera * getCamera() { return _camera; }
	~MasterRenderer();
};

class Renderer
{
protected:
	GLuint _vertex_shader_id, _fragment_shader_id, _program_id;
	MasterRenderer* _renderer;
public:
	virtual void render() = 0;
protected:
	GLuint genShader(const char* source_file_path, GLenum shader_type);
	void clear();
private:
	virtual void getUniformLocations() = 0;
	virtual void getAttribLocations() = 0;
};

struct ChunkNode {
	ChunkNode* next;
	Chunk* chunk;
};

class ChunkRenderer :
	public Renderer
{
private:
	ChunkNode* _first_chunk_node;
	GLint _translation_matrix_loc, _rotation_matrix_loc, _projection_matrix_loc, _chunk_translation_matrix_loc;
private:
	void renderChunk(Chunk * chunk);
public:
	ChunkRenderer(MasterRenderer* renderer, const char* vertex_shader_file_path, const char* _fragment_shader_file_path);
	void getUniformLocations() override;
	void getAttribLocations() override;
	void render() override;
	void addToRenderList(Chunk* chunk);
	~ChunkRenderer();
};

