#pragma once

namespace mb {

	enum class EventType
	{
		WindowCloseEvent, WindowResizeEvent,
		KeyPressedEvent, KeyReleasedEvent, KeyTypedEvent,
		MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseScrolledEvent, MouseMovedEvent, MouseEnterEvent, MouseLeaveEvent
	};

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
	public:
		bool Handled = false;
	};
	
	class EventDispatcher
	{
	public:
		EventDispatcher(Event* event)
			: m_Event(event)
		{

		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event->GetType() == T::GetStaticType())
			{
				m_Event->Handled = func(static_cast<T&>(*m_Event));
				return true;
			}

			return false;
		}
	private:
		Event* m_Event;
	};

}