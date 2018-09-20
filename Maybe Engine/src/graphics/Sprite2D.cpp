#include "Sprite2D.h"

namespace mb { namespace graphics {

	Sprite2D::Sprite2D(const maths::Vec2& position, const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f), m_BufferLayout(), m_VAO(),
		transform(maths::Vec2(position.x, position.y), maths::Vec2(1, 1), maths::Vec3(1, 1, 1), 0.0f)
	{
		float vertices[] = {
			-size.x / 2, -size.y / 2, 0,
			-size.x / 2,  size.y / 2, 0,
			 size.x / 2,  size.y / 2, 0,
			 size.x / 2, -size.y / 2, 0
		};

		m_Buffer = new Buffer(vertices, sizeof(float) * 3 * 4);
		m_BufferLayout.Push<float>(3);
		m_Buffer->SetLayout(m_BufferLayout);

		m_VAO.AddBuffer(m_Buffer);
	}

	Sprite2D::~Sprite2D()
	{
		if (m_Buffer)
			delete m_Buffer;
	}

	void Sprite2D::Bind() const
	{
		m_VAO.Bind();
	}

	void Sprite2D::Unbind() const
	{
		m_VAO.Unbind();
	}

} }