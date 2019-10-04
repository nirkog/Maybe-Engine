#include "Sprite2D.h"

namespace mb { namespace graphics {

	void Sprite2D::InitializeTransform(const maths::Vec2& position)
	{
		transform.position = maths::Vec2(position.x, position.y);
		transform.scale = maths::Vec2(1, 1);
		transform.rotationAxis = maths::Vec3(0, 0, 1);
		transform.rotationAngle = 0;
	}

	Sprite2D::Sprite2D(const maths::Vec2& position, const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Texture(nullptr), m_IsSpriteSheet(false)
	{
		InitializeTransform(position);
	}

	Sprite2D::Sprite2D(const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Texture(nullptr), m_IsSpriteSheet(false)
	{
		InitializeTransform(maths::Vec2(0, 0));
	}

	Sprite2D::Sprite2D()
		: m_Size(0, 0), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Texture(nullptr), m_IsSpriteSheet(false)
	{
		InitializeTransform(maths::Vec2(0, 0));
	}

	Sprite2D::~Sprite2D()
	{
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