#pragma once

#include <sstream>

#include "Window.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Sprite2D.h"

#include "..\utils\utils.h"
#include "..\platform\Entity.h"

#define MAX_TEXTURES 32

namespace mb { namespace graphics {

	struct VertexData
	{
		float positionX, positionY, positionZ;
		maths::Vec2 uv;
		float tid;
		maths::Vec3 color;
	};

	struct RotationData
	{
		maths::Vec3 axis;
		float angle;
	};

	class BatchRenderer
	{
	public:
		BatchRenderer(const Window& window);
		~BatchRenderer();

		void Begin();
		void Submit(const Sprite2D* sprite);
		void Submit(platform::Entity& entity);
		void Submit(platform::TransformComponent* transform, platform::RenderComponent* render);
		//void Submit(const Light& light);
		void End();
	private:
		void Flush();
		void Submit(const Sprite2D* sprite, const maths::Vec2& position, const maths::Vec2& scale, const RotationData& rotation);
	private:
		VertexArray m_VAO;
		BufferLayout m_VBOLayout;
		Buffer* m_VBO;

		IndexBuffer* m_IBO;
		VertexData* m_Buffer;
		Shader m_Shader;

		maths::Mat4 m_View, m_Proj;

		unsigned int m_SpriteCount;

		utils::Timer m_Timer;
		const Window& window;

		maths::Vec2 defaultUV[4];

		Texture* m_BoundTextures[MAX_TEXTURES];
		unsigned int m_TextureCount;
	};

} }