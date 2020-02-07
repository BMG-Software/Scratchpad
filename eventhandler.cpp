#include "eventhandler.h"

using namespace Logic;

bool EventHandler::HandleEvents()
{
	bool retVal = true;
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				retVal = false;
			}

			// Any other key events can happily go here :)

		}
	}
	return retVal;
}