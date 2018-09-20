#pragma once

#include "..\maths\maths.h"
#include "Buffer.h"
#include "VertexArray.h"

namespace mb { namespace graphics {

	class Sprite2D
	{
	public:
		Sprite2D(const maths::Vec2& position, const maths::Vec2& size);
		~Sprite2D();

		void SetPosition(const maths::Vec2& position);
		void SetSize(const maths::Vec2& size);
		inline void SetColor(const maths::Vec3 color) { m_Color = color; }

		inline const maths::Vec2 GetPosition() const { return m_Position; }
		inline const maths::Vec2 GetSize() const { return m_Size; }
		inline const maths::Vec3 GetColor() const { return m_Color; }

		inline const VertexArray GetVAO() const { return m_VAO; }

		void Bind() const;
		void Unbind() const;
	private:
		maths::Vec2 m_Position;
		maths::Vec2 m_Size;
		maths::Vec3 m_Color;

		Buffer *m_Buffer;
		BufferLayout m_BufferLayout;
		VertexArray m_VAO;

		float m_Vertices[3 * 4];
	};

} }