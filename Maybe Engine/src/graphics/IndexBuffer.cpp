#include "IndexBuffer.h"

namespace mb {

	IndexBuffer::IndexBuffer()
		: m_ID(0)
	{
		GLCall(glGenBuffers(1, &m_ID));
	}

	IndexBuffer::IndexBuffer(const void* data, const unsigned int size)
		: m_ID(0)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::SetData(const void* data, const unsigned int size)
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}