

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>

#include "camera.h"

namespace Logic
{

	class EventHandler
	{

	public:
		EventHandler() = default;
		virtual ~EventHandler() = default;

        void SetCamera(Graphics::Camera *camera);

		// Handles SDL events. Returns false if quit event fired
		bool HandleEvents();

    private:
        Graphics::Camera *m_Camera;

	};

}


#endif // EVENTHANDLER_H
