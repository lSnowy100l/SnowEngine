#pragma once
#include "MasterRenderer.h"
#include "TextPanel.h"

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	GLfloat data[] = { 0.00078125, 0, 0, 0, 0, 0.00138888888888888888888888888888, 0, 0, 0, 0, 1, 0, -1, -1, 0, 1 };
	glUniformMatrix4fv(_toPixelsMatrixLoc, 1, GL_FALSE, &data[0]);
	for (GUI* gui : gui_list) {
		TextPanel* tp = (TextPanel*)gui;
		tp->update();
		glBindVertexArray(gui->getVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindTexture(GL_TEXTURE_2D, gui->getTexture()->getId());
		glDrawArrays(GL_TRIANGLES, 0, gui->getVertexCount());
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glUseProgram(NULL);
}

void GUIRenderer::addGUI(GUI* gui) {
	gui_list.push_back(gui);
}

void GUIRenderer::getAttribLocations() {
	glBindAttribLocation(_programId, 0, "position");
	glBindAttribLocation(_programId, 1, "texCoords");
}

void GUIRenderer::getUniformLocations() {
	_toPixelsMatrixLoc = glGetUniformLocation(_programId, "toPixelsMatrix");
	_textureSamplerLoc = glGetUniformLocation(_programId, "texture");
}