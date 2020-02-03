
#include <SDL.h>
#include "gamecontroller.h"

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
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
