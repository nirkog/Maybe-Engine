#include "Buffer.h"


namespace mb { namespace graphics {

	unsigned int Buffer::m_ActiveBuffer = 0;

	Buffer::Buffer(const void* data, const unsigned int size, GLenum usage)
		: m_ID(0)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	Buffer::~Buffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void Buffer::Bind() const
	{
		if (m_ActiveBuffer != m_ID)
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
			m_ActiveBuffer = m_ID;
		}
	}

	void Buffer::Unbind() const
	{
		if (m_ActiveBuffer != 0)
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			m_ActiveBuffer = 0;
		}
	}

	void Buffer::SetLayout(BufferLayout& layout)
	{
		m_Layout = layout;
	}

} }