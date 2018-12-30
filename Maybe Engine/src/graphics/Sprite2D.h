#pragma once

#include "..\maths\maths.h"
#include "..\utils\Log.h"
#include "Texture.h"

namespace mb { namespace graphics {

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
		void SetTexture(const Texture* texture);

		inline const maths::Vec2& GetSize() const { return m_Size; }
		inline const maths::Vec3& GetColor() const { return m_Color; }

		inline const char* GetTexturePath() const { return m_TexturePath; }

		inline bool HasTexture() const { return m_Texture != nullptr; }

		inline Texture* GetTexture() const { return m_Texture; }

		void Bind() const;
		void Unbind() const;
	private:
		void InitializeTransform(const maths::Vec2& position);
	public:
		Transform transform;
	private:
		maths::Vec2 m_Size;
		maths::Vec3 m_Color;

		Texture* m_Texture;

		char* m_TexturePath;
	};

} }