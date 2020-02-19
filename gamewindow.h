

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include <linmath.h>
#include <SDL_opengl.h>
#undef main

#include <vector>

#include "glshaderloader.h"
#include "logger.h"
#include "objmodelloader.h"

namespace Graphics
{

	class GameWindow
	{

	public:

		GameWindow();
		virtual ~GameWindow();

		void AddDrawableObject(ObjModel* model); // TODO: need a remove as well at some point

		void Draw(); // Update the screen with the rendered content

	private:

		void HandleGLErrors(GLenum err);
		void GenerateMVPMatrix(mat4x4 mvp);
		void AnimateMVP(mat4x4 mvp); // adds a little bit of animation to spin models


		Logger &m_Logger;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;

		GLShaderLoader m_ShaderLoader;
		GLuint m_ShaderProgram, m_VBO, m_CBO, m_IBO, m_MatrixID;

		mat4x4 m_MVP;

		GLint m_AttributeCoord3d, m_AttributeColour;

		std::vector<ObjModel*> m_Models;

	};


}



#endif // GAMEWINDOW_H
