#include "IndexBuffer.h"

namespace mb { namespace graphics {

	unsigned int IndexBuffer::m_ActiveBuffer = 0;

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
		if (m_ActiveBuffer != m_ID)
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
			m_ActiveBuffer = m_ID;
		}
	}

	void IndexBuffer::Unbind() const
	{
		if (m_ActiveBuffer != 0)
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			m_ActiveBuffer = 0;
		}
	}

}}