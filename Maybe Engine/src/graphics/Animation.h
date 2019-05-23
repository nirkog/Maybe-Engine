#pragma once

#include "Sprite2D.h"
#include "..\utils\Timer.h"
#include "..\maths\vec2.h"

namespace mb { namespace graphics {

	class Animation
	{
	public:
		Animation();
		//Animation(const maths::Vec2 startingPosition, const maths::Vec2 endingPosition);
		~Animation();

		void Update();

		void SetFPS(const float fps) { m_FPS = fps; }

		void SetRows(const unsigned int rows) { m_Rows = rows; }
		void SetColumns(const unsigned int columns) { m_Columns = columns; }

		void SetStartingPosition(const unsigned int x, const unsigned int y) { m_StartPosition = { (float) x, (float) y }; m_Position = { (float) x, (float) y }; }
		void SetEndingPosition(const unsigned int x, const unsigned int y) { m_EndPosition = { (float) x, (float) y }; }

		void SetSpriteSheet(SpriteSheet sheet) { m_Rows = sheet.rows; m_Columns = sheet.columns; }

		const unsigned int GetRows() const { return m_Rows; }
		const unsigned int GetColumns() const { return m_Columns; }

		void Enable() { m_Enabled = true; }
		void Disable() { m_Enabled = false; }

		const bool Enabled() const { return m_Enabled; }

		const maths::Vec2 GetPosition() const { return m_Position; }
	private:
		unsigned int m_Rows, m_Columns;
		utils::Timer timer;
		float m_FPS;
		maths::Vec2 m_Position;
		maths::Vec2 m_StartPosition, m_EndPosition;
		bool m_Enabled;
	};

} }