

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include <linmath.h>
#include <SDL_opengl.h>
#undef main

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

		// Draw a drawable game entity in the renderer
		void Render(/*DrawableObject &obj*/);
		// Update the screen with the rendered content
		void Draw();

		//GameWindow(GameWindow const&) = delete;
		//void operator=(GameWindow const&) = delete;

	private:

		void HandleGLErrors(GLenum err);

		void GenerateMVPMatrix(mat4x4 mvp);

		Logger &m_Logger;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;

		GLShaderLoader m_ShaderLoader;
		GLuint m_ShaderProgram, m_VBO, m_CBO, m_IBO, m_MatrixID;

		mat4x4 m_MVP;

		GLint m_AttributeCoord3d, m_AttributeColour;

		ObjModel obj;
		ObjModelLoader loader;

	};


}



#endif // GAMEWINDOW_H
