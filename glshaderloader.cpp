#include "glshaderloader.h"

#include <cstdlib>
#include <fstream>

using namespace Graphics;

static const int ShaderBufferSize = 4096; // Limit to the length of the shaders in characters

Graphics::GLShaderLoader::GLShaderLoader() : m_Logger(Logger::Get())
{
}

GLuint GLShaderLoader::GetShaderProgram(const char * vsFilename, const char * fsFilename)
{
	char vsShaderSource[ShaderBufferSize];
	FileReader(vsFilename, vsShaderSource, ShaderBufferSize);
	GLuint vertexShader = LoadShader(vsShaderSource, GL_VERTEX_SHADER);
	char fsShaderSource[ShaderBufferSize];
	FileReader(fsFilename, fsShaderSource, ShaderBufferSize);
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
		m_Logger.LogError(log);
		free(log);
	}
	if (!success)
	{
		m_Logger.LogError("Error linking shaders");
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
		m_Logger.LogError(log);
	}
	if (!success)
	{
		m_Logger.LogError("Error loading shader");
	}
	free(log);
	return shader;
}

bool GLShaderLoader::FileReader(const char * filename, char* buffer, int bufferSize)
{
	std::ifstream filestream(filename);
	char c;
	int i;
	for (i = 0; filestream.get(c); i++)
	{
		if (i >= bufferSize)
		{
			m_Logger.LogError("Shader larger than allocated buffer");
			return false;
		}
		else 
		{
			buffer[i] = (char)c;
		}
	}
	buffer[i] = '\0';
	return true;
}
