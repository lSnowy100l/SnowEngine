#pragma once

#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vec3GLf.h"
#include "Chunk.h"
#include "Camera.h"
#include "GUI.h"

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
	virtual void getUniformLocations() = 0;
	virtual void getAttribLocations() = 0;
};

struct ChunkNode {
	ChunkNode* next;
	Chunk* chunk;
};

class ChunkRenderer : public Renderer {
private:
	ChunkNode* first_Chunk;
	GLint translationMatrixLoc, rotationMatrixLoc, projectionMatrixLoc, chunkTranslationMatrixLoc;
private:
	void renderChunk(Chunk * chunk);
public:
	ChunkRenderer(MasterRenderer* renderer, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	void getUniformLocations();
	void getAttribLocations();
	void render();
	void addToRenderList(Chunk* chunk);
	~ChunkRenderer();
};

class GUIRenderer : public Renderer {
private:
	std::vector<GUI*> gui_list;
	GLint _toPixelsMatrixLoc, _textureSamplerLoc;
public:
	GUIRenderer(MasterRenderer* renderer, const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	void getUniformLocations();
	void getAttribLocations();
	void addGUI(GUI* gui);
	void render();
};

