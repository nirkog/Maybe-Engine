#include "Animation.h"

namespace mb { namespace graphics {

	Animation::Animation()
		: m_Position(0, 0), m_StartPosition(0, 0), m_EndPosition(0, 0), m_Enabled(false), m_FPS(30)
	{

	}

	Animation::~Animation()
	{

	}
	
	void Animation::Update()
	{
		if (timer.Time() >= 1 / m_FPS)
		{
			timer.Clear();
			m_Position.x++;

			if (m_Position.x == m_EndPosition.x + 1 && m_Position.y == m_EndPosition.y)
			{
				m_Position = m_StartPosition;
			}

			if (m_Position.x >= m_Columns)
			{
				m_Position.x = 0;
				m_Position.y--;

				if (m_Position.y <= 0)
					m_Position.y = 0;
			}
		}
	}

} }