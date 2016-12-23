#pragma once

#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vec3GLf.h"
#include "Chunk.h"
#include "Camera.h"

class Renderer;

class MasterRenderer
{
private:
	Camera* _camera;
	std::vector<Renderer*> _renderers;
	double _s = 0, _a = 0;
public:
	MasterRenderer(Camera* camera);
	void renderAll();
	void addRenderer(Renderer* renderer) { _renderers.push_back(renderer); }
	inline double getFps() { return 1 / (_a - _s); }
	inline Camera* getCamera() { return _camera; }
	~MasterRenderer();
};

class Renderer
{
protected:
	GLuint _vertexShaderId, _fragmentShaderId, _programId;
	MasterRenderer* _renderer;
public:
	virtual void render() = 0;
protected:
	GLuint genShader(const char* filePath, GLenum type);
	void clear();
private:
	virtual void bindAtributes() = 0;
};

struct ChunkNode {
	ChunkNode* next;
	const Chunk* chunk;
};

class ChunkRenderer : public Renderer {
private:
	ChunkNode* first_Chunk;
	GLint translationMatrixLoc, rotationMatrixLoc, projectionMatrixLoc;
private:
	void renderChunk(const Chunk * chunk);
public:
	ChunkRenderer(MasterRenderer* renderer, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	void bindAtributes();
	void render();
	void addToRenderList(const Chunk* chunk);
	~ChunkRenderer();
};

