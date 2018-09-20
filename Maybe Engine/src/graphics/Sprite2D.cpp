#include "Sprite2D.h"

namespace mb { namespace graphics {

	Sprite2D::Sprite2D(const maths::Vec2& position, const maths::Vec2& size)
		: m_Position(position.x, position.y), m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f), m_BufferLayout(), m_VAO()
	{
		float vertices[] = {
			-size.x, -size.y, 0,
			-size.x,  size.y, 0,
			 size.x,  size.y, 0,
			 size.x, -size.y, 0
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