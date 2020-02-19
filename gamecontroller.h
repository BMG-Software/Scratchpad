

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "gamewindow.h"
#include "eventhandler.h"
#include "objmodelloader.h"

namespace Logic
{

	class GameController
	{

	public:
		GameController();
		virtual ~GameController() = default;

		// Runs up the main loop of the game
		void Run();

	private:
		Graphics::GameWindow m_GameWindow;
		EventHandler m_EventHandler;
		Graphics::ObjModelLoader m_ModelLoader;

	};


}



#endif // GAMECONTROLLER_H
