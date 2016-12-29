#pragma once
#include "MasterRenderer.h"

GUIRenderer::GUIRenderer(MasterRenderer* renderer, const char* vertexShaderFilePath, const char* fragmentShaderFilePath) {
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

void GUIRenderer::render() {
	glUseProgram(_programId);
	
	for (GUI* gui : gui_list) {
		glBindVertexArray(gui->getVaoId());
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
	glUseProgram(NULL);
}

void GUIRenderer::addGUI(GUI* gui) {
	gui_list.push_back(gui);
}

void GUIRenderer::getAttribLocations() {
	glBindAttribLocation(_programId, 0, "position");
}

void GUIRenderer::getUniformLocations() {

}