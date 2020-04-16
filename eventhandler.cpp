#include "eventhandler.h"

using namespace Logic;


// Use a map to map keys to callbacks. Run through the keys and callbacks together

Logic::EventHandler::EventHandler()
{
}

void Logic::EventHandler::SetCamera(Camera * camera)
{
    m_Camera = camera;
}

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
            else if (e.key.keysym.sym == SDLK_UP)
            {
                m_Camera->UpdatePosition(0.f, 0.f, -0.1f);
            }
            else if (e.key.keysym.sym == SDLK_DOWN)
            {
                m_Camera->UpdatePosition(0.f, 0.f, 0.1f);
            }

			// Any other key events can happily go here :)

		}
	}
	return retVal;
}
