#include "Buffer.h"


namespace mb { namespace graphics {

	Buffer::Buffer(const void* data, const unsigned int size, GLenum usage)
		: m_ID(0)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void Buffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void Buffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Buffer::SetLayout(BufferLayout& layout)
	{
		m_Layout = layout;
	}

} }