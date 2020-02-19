
#include <SDL.h>
#include "gamecontroller.h"

int WinMain()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // TODO: Move SDL specific stuff into gamewindow
	{
		// TODO: Log success
		Logic::GameController gameController;
		gameController.Run();
	}
	else
	{
		// TODO: Log failure
	}
	SDL_Quit();
	return 0;
}
