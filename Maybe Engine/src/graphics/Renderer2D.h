#pragma once

#include "Sprite2D.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Window.h"

namespace mb { namespace graphics {

	class Renderer2D
	{
	public:
		Renderer2D(const Window& window);
		~Renderer2D();

		void Draw(const Sprite2D& sprite);
	private:
		IndexBuffer *m_IBO;
		Shader m_BasicShader;
		//unsigned short m_Indices[6];

		maths::Mat4 proj;
		maths::Mat4 view;
	};

} }