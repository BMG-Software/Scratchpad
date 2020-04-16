

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include <linmath.h>
#include <SDL_opengl.h>
#undef main

#include <vector>
#include <memory>

#include "glshaderloader.h"
#include "logger.h"
#include "objmodelloader.h"
#include "camera.h"

namespace Graphics
{

	class GameWindow
	{

	public:

		GameWindow();
		virtual ~GameWindow();

        void SetCamera(Camera *camera);

		void AddDrawableObject(ObjModel* model); // TODO: need a remove as well at some point

		void Draw(); // Update the screen with the rendered content

	private:

		void HandleGLErrors(GLenum err);
		void UpdateMVPMatrix(mat4x4 mvp);

		Logger &m_Logger;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;

		GLShaderLoader m_ShaderLoader;
		GLuint m_ShaderProgram, m_VBO, m_IBO, m_MatrixID, m_TextureID, m_TexCoords;

		mat4x4 m_MVP;

		GLint m_AttributeCoord3d, m_AttributeTexture, m_UniformTexture;

		std::vector<ObjModel*> m_Models;

        Camera *m_Camera;

	};


}



#endif // GAMEWINDOW_H
