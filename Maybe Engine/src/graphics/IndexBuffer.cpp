#include "IndexBuffer.h"

#include <GL\glew.h>

namespace mb { namespace graphics {

	unsigned int IndexBuffer::m_ActiveBuffer = 0;

	IndexBuffer::IndexBuffer(const void* data, const unsigned int size)
		: m_ID(0)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void IndexBuffer::Bind() const
	{
		if (m_ActiveBuffer != m_ID)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
			m_ActiveBuffer = m_ID;
		}
	}

	void IndexBuffer::Unbind() const
	{
		if (m_ActiveBuffer != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			m_ActiveBuffer = 0;
		}
	}

}}