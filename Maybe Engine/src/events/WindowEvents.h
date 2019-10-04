#pragma once

#include "Event.h"

namespace mb {

	class WindowCloseEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowCloseEvent; }
		EventType GetType() const { return GetStaticType(); }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{

		}

		static EventType GetStaticType() { return EventType::WindowResizeEvent; }
		EventType GetType() const { return GetStaticType(); }

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
	private:
		unsigned int m_Width, m_Height;
	};

}