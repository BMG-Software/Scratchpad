

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>

namespace Logic
{

	class EventHandler
	{

	public:
		EventHandler() = default;
		virtual ~EventHandler() = default;

		// Handles SDL events. Returns false if quit event fired
		bool HandleEvents();

	};

}


#endif // EVENTHANDLER_H
