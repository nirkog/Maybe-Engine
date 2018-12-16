#include "Sprite2D.h"

namespace mb { namespace graphics {

	Sprite2D::Sprite2D(const maths::Vec2& position, const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f),
		transform(maths::Vec2(position.x, position.y), maths::Vec2(1, 1), maths::Vec3(0, 0, 1), 0.0f),
		m_Texture(nullptr)
	{
	}

	Sprite2D::Sprite2D()
		: m_Size(0, 0), m_Color(1.0f, 1.0f, 1.0f),
		transform(maths::Vec2(0, 0), maths::Vec2(1, 1), maths::Vec3(0, 0, 1), 0.0f),
		m_Texture(nullptr)
	{
	}

	Sprite2D::~Sprite2D()
	{
		std::cout << "Destorying" << std::endl;
	}

	void Sprite2D::Bind() const
	{
		if (m_Texture)
			m_Texture->Bind();
	}

	void Sprite2D::Unbind() const
	{
		if(m_Texture)
			m_Texture->Unbind();
	}

	void Sprite2D::SetTexture(const Texture* texture)
	{
		m_Texture = (Texture*) texture;
	}

} }