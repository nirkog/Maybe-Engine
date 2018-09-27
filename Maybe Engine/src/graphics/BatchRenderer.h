#pragma once

#include "Window.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Sprite2D.h"

#include "..\maths\maths.h"

namespace mb { namespace graphics {

	struct VertexData
	{
		maths::Vec4 position;
		maths::Vec3 color;
	};

	class BatchRenderer
	{
	public:
		BatchRenderer(const Window& window);
		~BatchRenderer();

		void Submit(const Sprite2D& sprite);
		void Flush();
	private:
		Buffer* m_Buffer;
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Shader m_Shader;

		VertexData* m_BufferPointer;

		maths::Mat4 m_View;
		maths::Mat4 m_Proj;

		unsigned int m_SpriteCount;
	};

} }