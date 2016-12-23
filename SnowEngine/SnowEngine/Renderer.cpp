#include "MasterRenderer.h"

GLuint Renderer::genShader(const char * filePath, GLenum type) {
	std::ifstream in(filePath);
	std::stringstream buffer;
	buffer << in.rdbuf();
	std::string contents(buffer.str());
	GLuint shaderId = glCreateShader(type);
	const GLchar *source = (const GLchar *)contents.c_str();
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);
	GLint isCompiled = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
		for (GLchar c : errorLog) {
			std::cout << c;
		}
		glDeleteShader(shaderId);
		return 0;
	}
	return shaderId;
}

void Renderer::clear()
{
	glUseProgram(NULL);
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
	glDeleteProgram(_programId);
}
