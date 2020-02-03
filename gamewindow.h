

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#undef main

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

	private:

		GameWindow();
		virtual ~GameWindow();

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

	};


}



#endif // GAMEWINDOW_H
