#pragma once

#include "..\maths\maths.h"
#include "..\utils\Log.h"
#include "Texture.h"
#include "Color.h"

namespace mb { namespace graphics {

	struct Transform
	{
		maths::Vec2 position, scale;
		maths::Vec3 rotationAxis;
		float rotationAngle;
	};

	struct SpriteSheet
	{
		unsigned int columns, rows;
	};

	class Sprite2D
	{
	public:
		Sprite2D(const maths::Vec2& position, const maths::Vec2& size);
		Sprite2D(const maths::Vec2& size);
		Sprite2D();
		~Sprite2D();

		inline void SetColor(const Color color) { m_Color = color; }
		inline void SetColor(const char* hex) { m_Color = { hex }; }
		inline void SetColor(const float r, const float g, const float b, const float a) { m_Color = { r, g, b, a }; }
		void SetTexture(const Texture* texture);

		inline void SetSpriteSheet(SpriteSheet sheet) { m_SpriteSheet = sheet; };
		inline void EnableSpriteSheet() { m_IsSpriteSheet = true; } 
		inline void DisableSpriteSheet() { m_IsSpriteSheet = false; }

		inline void SetSpriteSheetPosition(const unsigned int x, unsigned int y) { m_SpriteSheetPosition = { float(x), float(y) }; }

		inline const maths::Vec2& GetSize() const { return m_Size; }
		inline const Color& GetColor() const { return m_Color; }

		inline const char* GetTexturePath() const { return m_TexturePath; }

		inline bool HasTexture() const { return m_Texture != nullptr; }

		inline Texture* GetTexture() const { return m_Texture; }

		inline bool IsSpriteSheet() const { return m_IsSpriteSheet; }
		inline const SpriteSheet& GetSpriteSheet() const { return m_SpriteSheet; }
		inline const maths::Vec2& GetSpriteSheetPosition() const { return m_SpriteSheetPosition; }

		void Bind() const;
		void Unbind() const;
	private:
		void InitializeTransform(const maths::Vec2& position);
	public:
		Transform transform;
	private:
		maths::Vec2 m_Size;
		Color m_Color;

		Texture* m_Texture;

		char* m_TexturePath;

		SpriteSheet m_SpriteSheet;
		bool m_IsSpriteSheet;
		maths::Vec2 m_SpriteSheetPosition;
	};

} }