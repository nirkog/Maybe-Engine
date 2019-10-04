#pragma once

#include <memory>

#include "../core/math/vec3.h"
#include "../core/math/vec4.h"
#include "VertexArray.h"
#include "Shader.h"

namespace mb {

	class Renderer
	{
	public:
		struct VertexData {
			Vec3 position;
			Vec4 color;
		};
	public:
		Renderer();

		void Begin();
		void End();

		void Submit(const Vec2& size, const Vec3& position, const Vec4& color);
	private:
		void Flush();
	private:
		VertexArray m_VAO;
		VertexBufferLayout m_VBOLayout;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;
		VertexData* m_VBOPointer;
		Shader m_Shader;

		unsigned int m_SpriteCount;
	};

}