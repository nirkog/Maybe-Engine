#pragma once

#include "..\maths\maths.h"
#include "Buffer.h"
#include "VertexArray.h"

namespace mb { namespace graphics {

	struct Transform
	{
		maths::Vec2 position, scale;
		maths::Vec3 rotationAxis;
		float rotationAngle;

		Transform(maths::Vec2 position, maths::Vec2 scale, maths::Vec3 rotationAxis, float angle)
			: position(position.x, position.y), scale(scale.x, scale.y), rotationAxis(rotationAxis.x, rotationAxis.y, rotationAxis.z), rotationAngle(angle) {}
	};

	class Sprite2D
	{
	public:
		Sprite2D(const maths::Vec2& position, const maths::Vec2& size);
		~Sprite2D();

		/*void SetPosition(const maths::Vec2& position);
		void SetScale(const maths::Vec2& scale);
		void SetRotation(float angle, const maths::Vec3& axis);*/
		inline void SetColor(const maths::Vec3 color) { m_Color = color; }

		inline const maths::Vec2 GetSize() const { return m_Size; }
		inline const maths::Vec3 GetColor() const { return m_Color; }

		inline const VertexArray GetVAO() const { return m_VAO; }

		void Bind() const;
		void Unbind() const;
	public:
		Transform transform;
	private:
		maths::Vec2 m_Size;
		maths::Vec3 m_Color;

		Buffer *m_Buffer;
		BufferLayout m_BufferLayout;
		VertexArray m_VAO;
	};

} }