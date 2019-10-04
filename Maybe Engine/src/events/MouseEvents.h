#pragma once

#include "../core/math/Vec2.h "

namespace mb
{
	enum class MouseButton
	{
		BUTTON_0 = 0,
		BUTTON_1 = 1,
		BUTTON_2 = 2,
		BUTTON_3 = 3,
		BUTTON_4 = 4,
		BUTTON_5 = 5,
		BUTTON_6 = 6,
		BUTTON_7 = 7,
		BUTTON_8 = 8,
		BUTTON_9 = 9,
		BUTTON_LAST = BUTTON_8,
		BUTTON_LEFT = BUTTON_1,
		BUTTON_RIGHT = BUTTON_2,
		BUTTON_MIDDLE = BUTTON_3
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline MouseButton GetMouseButton() const { return m_Button; }
	protected:
		MouseButtonEvent(int button)
			: m_Button((MouseButton)button) {}

		MouseButton m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonPressedEvent; }
		EventType GetType() const { return GetStaticType(); }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleasedEvent; }
		EventType GetType() const { return GetStaticType(); }
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_Offset(xOffset, yOffset) {}
		
		inline const Vec2& GetOffset() const { return m_Offset; }

		static EventType GetStaticType() { return EventType::MouseScrolledEvent; }
		EventType GetType() const { return GetStaticType(); }
	private:
		Vec2 m_Offset;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_Position(x, y) {}
		
		inline const Vec2& GetPosition() const { return m_Position; }

		static EventType GetStaticType() { return EventType::MouseMovedEvent; }
		EventType GetType() const { return GetStaticType(); }
	private:
		Vec2 m_Position;
	};

	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent() {}

		static EventType GetStaticType() { return EventType::MouseEnterEvent; }
		EventType GetType() const { return GetStaticType(); }
	};

	class MouseLeaveEvent : public Event
	{
	public:
		MouseLeaveEvent() {}

		static EventType GetStaticType() { return EventType::MouseLeaveEvent; }
		EventType GetType() const { return GetStaticType(); }
	};
}