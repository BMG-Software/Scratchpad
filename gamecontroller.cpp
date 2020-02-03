#include "gamecontroller.h"

using namespace Logic;

GameController::GameController() : m_GameWindow(Graphics::GameWindow::Get())
{
}

void GameController::Run()
{
	while (m_EventHandler.HandleEvents())
	{
		SDL_Delay(50); // Temporary delay just so the game doesn't run too fast yet

		m_GameWindow.Draw();
	}

}
