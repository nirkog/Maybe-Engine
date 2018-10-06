#pragma once

#include "Window.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Sprite2D.h"

#include "..\utils\utils.h"

namespace mb { namespace graphics {

	struct VertexData
	{
		//maths::Vec3 position;
		float positionX, positionY, positionZ;
		maths::Vec3 color;
	};

	class BatchRenderer
	{
	public:
		BatchRenderer(const Window& window);
		~BatchRenderer();

		void Begin();
		void Submit(const Sprite2D* sprite);
		void End();
	private:
		void Flush();
	private:
		unsigned int m_VBO, m_VAO, m_IBO;
		VertexData* m_Buffer;

		Shader m_Shader;

		maths::Mat4 m_View, m_Proj;

		unsigned int m_SpriteCount;

		utils::Timer m_Timer;

		const Window& window;
	};

} }