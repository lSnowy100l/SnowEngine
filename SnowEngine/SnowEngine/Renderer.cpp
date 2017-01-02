#include "MasterRenderer.h"

GLuint Renderer::genShader(const char * filePath, GLenum type) {
	// Source file read
	std::ifstream in(filePath);
	std::stringstream buffer;
	buffer << in.rdbuf();
	std::string contents(buffer.str());
	GLuint shaderId = glCreateShader(type);
	const GLchar *source = (const GLchar *)contents.c_str();

	// Shader upload and compilation
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);

	//Error comprobation
	GLint isCompiled = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderId);
		errorLog.push_back('\n'); // Add null termination to the array
		terror(&errorLog[0], 1);
		return 0;
	}
	return shaderId;
}

void Renderer::clear() {
	glUseProgram(NULL);
	glDetachShader(_program_id, _vertex_shader_id);
	glDetachShader(_program_id, _fragment_shader_id);
	glDeleteShader(_vertex_shader_id);
	glDeleteShader(_fragment_shader_id);
	glDeleteProgram(_program_id);
}
