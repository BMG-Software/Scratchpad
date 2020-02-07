
#ifndef GLSHADERLOADER_H
#define GLSHADERLOADER_H

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace Graphics
{

	class GLShaderLoader
	{

	public:
		GLShaderLoader() = default;
		~GLShaderLoader() = default;

		GLuint GetShaderProgram(const char* vsFilename, const char* fsFilename);

	private:
		GLuint LoadShader(const char* shaderSource, GLenum shaderType);

	};

}

#endif // GLSHADERLOADER_H