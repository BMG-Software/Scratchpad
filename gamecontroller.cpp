#include "gamecontroller.h"

using namespace Logic;

GameController::GameController()
{
    m_GameWindow.SetCamera(&m_Camera);
    m_EventHandler.SetCamera(&m_Camera);
}

void GameController::Run()
{
	Graphics::ObjModel cube;
	m_ModelLoader.LoadModel("cube.obj", cube);



	m_GameWindow.AddDrawableObject(&cube);
	
	while (m_EventHandler.HandleEvents())
	{
		SDL_Delay(17); // Temporary delay just so the game doesn't run too fast yet

		m_GameWindow.Draw();
	}

}
