#include "Sprite2D.h"

namespace mb { namespace graphics {

	void Sprite2D::InitializeTransform(const maths::Vec2& position)
	{
		transform.position = maths::Vec2(position.x, position.y);
		transform.scale = maths::Vec2(1, 1);
		transform.rotationAxis = maths::Vec3(0, 0, 1);
		transform.rotationAngle = 0;

		m_DrawingMode = DrawingMode::TEXTURED;
		m_Shape = Shape::RECTANGLE;
		m_Radius = m_Size.x / 2;
		m_CirclePrecision = 25;
	}

	Sprite2D::Sprite2D(const maths::Vec2& position, const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Texture(nullptr)
	{
		InitializeTransform(position);
	}

	Sprite2D::Sprite2D(const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Texture(nullptr)
	{
		InitializeTransform(maths::Vec2(0, 0));
	}

	Sprite2D::Sprite2D()
		: m_Size(0, 0), m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_Texture(nullptr)
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

	void Sprite2D::SetRadius(float radius)
	{
		m_Radius = radius;
		GenerateVertices();
	}

	void Sprite2D::SetCirclePrecision(unsigned int precision)
	{
		m_CirclePrecision = precision;
		GenerateVertices();
	}

	void Sprite2D::GenerateVertices()
	{
		m_Vertices.clear();

		std::vector<maths::Vec2> points;
		float theta = 0;
		float x = 0, y = 0;
		float dTheta = (float) M_PI / m_CirclePrecision;

		while (theta < 2 * M_PI)
		{
			x = m_Radius * maths::cos(theta);
			y = m_Radius * maths::sin(theta);
			points.push_back({ x, y });
			theta += dTheta;
		}

		x = m_Radius * maths::cos(theta);
		y = m_Radius * maths::sin(theta);
		points.push_back({ x, y });

		for (unsigned int i = 0; i < points.size(); i++)
		{
			m_Vertices.push_back({ points[i].x, points[i].y, 0, 1 });
		}

		points.clear();
	}

} }