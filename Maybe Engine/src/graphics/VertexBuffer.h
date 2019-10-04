#pragma once

#include "VertexBufferLayout.h"

namespace mb {

	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(const void* data, const unsigned int size, GLenum usage = GL_STATIC_DRAW);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, const unsigned int size, GLenum usage = GL_STATIC_DRAW);

		inline void SetLayout(VertexBufferLayout& layout) { m_Layout = layout; }

		inline unsigned int GetID() const { return m_ID; }
		inline const VertexBufferLayout& GetLayout() const { return m_Layout; }
	private:
		unsigned int m_ID;
		VertexBufferLayout m_Layout;
	};
	
}