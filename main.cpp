
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include "gamecontroller.h"

const char *DefaultFilename = "monkey.obj"; // Load our monkey friend by default

int WinMain(HINSTANCE, HINSTANCE, PSTR lpCmdLine, INT)
{
    std::string filename(DefaultFilename);

    if (strcmp(lpCmdLine, "") != 0)
    {
        filename = std::string(lpCmdLine);
    }
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && (IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) == IMG_INIT_PNG) // TODO: Move SDL specific stuff into gamewindow
	{
		// TODO: Log success
		Logic::GameController gameController;
		gameController.Run(filename);
	}
	else
	{
		// TODO: Log failure
	}
	SDL_Quit();
	return 0;
}
