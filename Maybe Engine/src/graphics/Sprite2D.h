#pragma once

#include "..\maths\maths.h"
#include "..\utils\Log.h"
#include "Texture.h"

namespace mb { namespace graphics {

	enum DrawingMode
	{
		TEXTURED = 0, PRIMITIVE = 1
	};
	
	enum Shape
	{
		RECTANGLE = 0, TRIANGLE = 1, CIRCLE = 2, POLYGON = 3
	};

	struct Transform
	{
		maths::Vec2 position, scale;
		maths::Vec3 rotationAxis;
		float rotationAngle;
	};

	class Sprite2D
	{
	public:
		Sprite2D(const maths::Vec2& position, const maths::Vec2& size);
		Sprite2D(const maths::Vec2& size);
		Sprite2D();
		~Sprite2D();

		inline void SetColor(const maths::Vec3 color) { m_Color = color; }
		inline void SetDrawingMode(DrawingMode mode) { m_DrawingMode = mode; };
		inline void SetShape(Shape shape) { m_Shape = shape; }
		void SetCirclePrecision(unsigned int p);
		void SetRadius(float radius);
		void SetTexture(const Texture* texture);

		inline const maths::Vec2& GetSize() const { return m_Size; }
		inline const maths::Vec3& GetColor() const { return m_Color; }
		inline const DrawingMode GetDrawingMode() const { return m_DrawingMode; }
		inline const Shape GetShape() const { return m_Shape; }
		inline const float GetRadius() const { return m_Radius; }
		inline const std::vector<maths::Vec4> getVertices() const { return m_Vertices; }

		inline const char* GetTexturePath() const { return m_TexturePath; }

		inline bool HasTexture() const { return m_Texture != nullptr; }

		inline Texture* GetTexture() const { return m_Texture; }

		void Bind() const;
		void Unbind() const;
	private:
		void InitializeTransform(const maths::Vec2& position);
		void GenerateVertices();
	public:
		Transform transform;
	private:
		maths::Vec2 m_Size;
		maths::Vec3 m_Color;

		Texture* m_Texture;

		char* m_TexturePath;

		DrawingMode m_DrawingMode;
		Shape m_Shape;

		std::vector<maths::Vec4> m_Vertices;
		float m_Radius;
		unsigned int m_CirclePrecision;
	};

} }