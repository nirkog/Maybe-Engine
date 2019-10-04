#include "EventQueue.h"

namespace mb {

	List<Event*> EventQueue::m_Queue;

	void EventQueue::PushEvent(Event* e)
	{
		m_Queue.PushBack(e);
	}

	Event* EventQueue::Pop()
	{
		return m_Queue.PopFront();
	}

	unsigned int EventQueue::Count()
	{
		return m_Queue.Count();
	}

}