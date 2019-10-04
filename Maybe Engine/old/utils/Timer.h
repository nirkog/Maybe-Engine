#pragma once

#include <iostream>

namespace mb { namespace utils {

	enum TimeUnits
	{
		SECONDS, MILLISECONDS, MICROSECONDS
	};

	class Timer
	{
	public:
		inline Timer() : m_Time(0), m_TimeModifier(1), m_Interval(0), m_IntervalCount(0), m_HasInterval(false), m_ClearOnInterval(true), m_ID(0)
		{
			m_ID = AddToList(this);
		}

		inline Timer(TimeUnits unit)
			: m_Time(0), m_TimeModifier(1), m_Interval(0), m_IntervalCount(0), m_HasInterval(false), m_ClearOnInterval(true), m_ID(0)
		{
			SetUnits(unit);
			m_ID = AddToList(this);
		}

		inline ~Timer()
		{
			RemoveFromList(this);
		}

		inline void Update(float deltaTime) 
		{ 
			m_Time += deltaTime * m_TimeModifier;

			if (m_HasInterval)
			{
				if (m_Time >= m_Interval)
				{
					m_IntervalFunc(m_Interval);
					m_IntervalCount++;

					if(m_ClearOnInterval) Clear();
					else m_HasInterval = true;
				}
			}
		}

		inline void Clear() { m_Time = 0; }
		inline float Time() const { return m_Time; }

		inline void SetUnits(TimeUnits unit) 
		{
			if (unit == TimeUnits::SECONDS)
				m_TimeModifier = 1;
			else if (unit == TimeUnits::MILLISECONDS)
				m_TimeModifier = 1000;
			else if (unit == TimeUnits::MICROSECONDS)
				m_TimeModifier = 1000000;
		}

		inline void SetFunctionAtInterval(void(*func)(float interval), float interval)
		{
			m_IntervalFunc = func;
			m_Interval = interval;
			m_HasInterval = true;
		}

		inline void ChangeInterval(float interval)
		{
			m_Interval = interval;
		}

		inline void SetClearOnInterval(bool clear) { m_ClearOnInterval = clear; }

		inline void EnableInterval() { m_HasInterval = true; }
		inline void DisableInterval() { m_HasInterval = false; }

		inline void ClearIntervalCount() { m_IntervalCount = 0; }
		inline unsigned int GetIntervalCount() const { return m_IntervalCount; }

		inline unsigned int GetID() const { return m_ID; }

		inline void SetID(unsigned int id) { m_ID = id; }

		friend unsigned int AddToList(Timer* timer);
		friend void RemoveFromList(Timer* timer);

	private:
		float m_Time, m_Interval;
		unsigned int m_TimeModifier, m_IntervalCount, m_ID;
		void (*m_IntervalFunc)(float);
		bool m_ClearOnInterval, m_HasInterval;
	};

} }