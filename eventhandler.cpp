#include "eventhandler.h"

using namespace Logic;


// Use a map to map keys to callbacks. Run through the keys and callbacks together

void EventHandler::SetCamera(Graphics::Camera * camera)
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
            else if (e.key.keysym.sym == SDLK_w)
            {
                m_Camera->MoveForward();
            }
            else if (e.key.keysym.sym == SDLK_s)
            {
                m_Camera->MoveBackward();
            }
            else if (e.key.keysym.sym == SDLK_a)
            {
                m_Camera->StrafeLeft();
            }
            else if (e.key.keysym.sym == SDLK_d)
            {
                m_Camera->StrafeRight();
            }

			// Any other key events can happily go here :)

		}
	}
	return retVal;
}
