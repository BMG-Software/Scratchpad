

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "gamewindow.h"
#include "eventhandler.h"
#include "objmodelloader.h"
#include "camera.h"

namespace Logic
{

	class GameController
	{

	public:
		GameController();
		virtual ~GameController() = default;

		// Runs up the main loop of the game
		void Run(const std::string &objFilename);

	private:
		Graphics::GameWindow m_GameWindow;
		EventHandler m_EventHandler;
		Graphics::ObjModelLoader m_ModelLoader;
        Graphics::Camera m_Camera;
	};


}



#endif // GAMECONTROLLER_H
