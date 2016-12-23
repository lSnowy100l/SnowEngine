#include "MasterRenderer.h"



MasterRenderer::MasterRenderer(Camera* camera) : _camera(camera)
{
}

void MasterRenderer::renderAll()
{
	// Llama a todos los renderizadores a realizar sus respectivos cometidos.
	_s = _a;
	_a = glfwGetTime();
	for (Renderer* r : _renderers) {
		r->render();
	}
}


MasterRenderer::~MasterRenderer()
{
	// Elimina todos los renderizadores asociados al Master Renderer
	for (Renderer* r : _renderers) {
		delete r;
	}
}
