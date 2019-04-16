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
		m_CirclePrecision = 35.0f;
	}

	Sprite2D::Sprite2D(const maths::Vec2& position, const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f), m_Texture(nullptr)
	{
		InitializeTransform(position);
	}

	Sprite2D::Sprite2D(const maths::Vec2& size)
		: m_Size(size.x, size.y), m_Color(1.0f, 1.0f, 1.0f), m_Texture(nullptr)
	{
		InitializeTransform(maths::Vec2(0, 0));
	}

	Sprite2D::Sprite2D()
		: m_Size(0, 0), m_Color(1.0f, 1.0f, 1.0f), m_Texture(nullptr)
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

	void Sprite2D::SetCirclePrecision(float precision)
	{
		m_CirclePrecision = precision;
		GenerateVertices();
	}

	void Sprite2D::GenerateVertices()
	{
		m_Vertices.clear();

		std::vector<maths::Vec2> points;
		float rSquared = pow(m_Radius, 2);
		float x = -m_Radius, y = 0;
		float dx = m_Radius / m_CirclePrecision;

		while (x < m_Radius)
		{
			y = sqrt(rSquared - pow(x, 2));
			points.push_back({ x, y });

			x += dx;
		}

		x = m_Radius;
		y = sqrt(rSquared - pow(x, 2));
		points.push_back({ x, y });

		utils::Log::Debug("{}", points.size());

		while (x > -m_Radius)
		{

			y = -sqrt(rSquared - pow(x, 2));
			points.push_back({ x, y });

			x -= dx;
		}

		x = -m_Radius;
		y = sqrt(rSquared - pow(x, 2));
		points.push_back({ x, y });

		for (unsigned int i = 0; i < points.size(); i++)
		{
			m_Vertices.push_back({ points[i].x, points[i].y, 0, 1 });
		}

		points.clear();
	}

} }