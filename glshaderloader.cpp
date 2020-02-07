#include "glshaderloader.h"

#include <cstdlib>

using namespace Graphics;

GLuint GLShaderLoader::GetShaderProgram(const char * vsFilename, const char * fsFilename)
{
	const char* vsShaderSource = nullptr; // TODO: Read vertex shader content
	GLuint vertexShader = LoadShader(vsShaderSource, GL_VERTEX_SHADER);
	const char* fsShaderSource = nullptr; // TODO: Read frag shader content
	GLuint fragmentShader = LoadShader(fsShaderSource, GL_FRAGMENT_SHADER);


	GLint success, logLength;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar* log = (GLchar*)malloc(logLength);
		glGetProgramInfoLog(program, logLength, NULL, log);
		// m_Logger.LogError(log);
		free(log);
	}
	if (!success)
	{
		// m_Logger.LogError("Error linking shaders");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

GLuint Graphics::GLShaderLoader::LoadShader(const char * shaderSource, GLenum shaderType)
{
	GLchar *log = NULL;
	GLint success, logLength;
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	log = (GLchar*)malloc(logLength);
	if (logLength > 0)
	{
		glGetShaderInfoLog(shader, logLength, NULL, log);
		// m_Logger.LogError(log);
	}
	if (!success)
	{
		// m_Logger.LogError("Error loading shader");
	}
	free(log);
	return shader;
}
