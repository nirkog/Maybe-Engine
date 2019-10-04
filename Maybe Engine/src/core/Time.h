#pragma once

#include <chrono>

namespace mb {

	class TimePoint
	{
	public:
		TimePoint(float time)
			: m_Time(time)
		{

		}

		inline float Time() const { return m_Time; }

		TimePoint& operator=(const TimePoint& other)
		{
			m_Time = other.Time();

			return *this;
		}

		float operator+(const TimePoint& other)
		{
			return m_Time + other.Time();
		}

		float operator-(const TimePoint& other)
		{
			return m_Time - other.Time();
		}

		TimePoint& operator+=(const TimePoint& other)
		{
			m_Time += other.Time();

			return *this;
		}

		TimePoint& operator-=(const TimePoint& other)
		{
			m_Time -= other.Time();

			return *this;
		}
	private:
		float m_Time;
	};

	class Time
	{
	public:
		template<typename T = std::chrono::high_resolution_clock>
		static TimePoint Now()
		{
			auto now = T::now();

			std::cout << std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() << std::endl;

			return TimePoint(now.time_since_epoch().count());
		}
	};

}