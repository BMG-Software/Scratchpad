

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#undef main

#include "glshaderloader.h"
#include "logger.h"

namespace Graphics
{

	class GameWindow
	{

	public:
		
		static GameWindow &Get();

		// Draw a drawable game entity in the renderer
		void Render(/*DrawableObject &obj*/);
		// Update the screen with the rendered content
		void Draw();

		GameWindow(GameWindow const&) = delete;
		void operator=(GameWindow const&) = delete;

	private:

		GameWindow();
		virtual ~GameWindow();

		Logger &m_Logger;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;

		GLShaderLoader m_ShaderLoader;
		GLuint m_ShaderProgram, m_VBO;

		GLint m_AttributeCoord2d;

	};


}



#endif // GAMEWINDOW_H
