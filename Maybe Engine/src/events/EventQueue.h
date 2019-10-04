#pragma once

#include "../core/List.h"
#include "Event.h"

namespace mb {
	class EventQueue
	{
	public:
		static void PushEvent(Event* e);
		static Event* Pop();

		static unsigned int Count();
	private:
		static List<Event*> m_Queue;
	};
}