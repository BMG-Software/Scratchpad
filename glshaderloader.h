
#ifndef GLSHADERLOADER_H
#define GLSHADERLOADER_H

#include <GL/glew.h>
#include <SDL_opengl.h>

#include "logger.h"

namespace Graphics
{

	class GLShaderLoader
	{

	public:
		GLShaderLoader();
		~GLShaderLoader() = default;

		GLuint GetShaderProgram(const char* vsFilename, const char* fsFilename);

	private:
		GLuint LoadShader(const char* shaderSource, GLenum shaderType);
		bool FileReader(const char* filename, char* buffer, int bufferSize);

		Logger &m_Logger;

	};

}

#endif // GLSHADERLOADER_H