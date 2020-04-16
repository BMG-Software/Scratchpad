

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>

#include "camera.h"

namespace Logic
{

	class EventHandler
	{

	public:
		EventHandler();
		virtual ~EventHandler() = default;

        void SetCamera(Camera *camera);

		// Handles SDL events. Returns false if quit event fired
		bool HandleEvents();

    private:
        Camera *m_Camera;

	};

}


#endif // EVENTHANDLER_H
