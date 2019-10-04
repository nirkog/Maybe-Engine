#include "VertexBuffer.h"

namespace mb {

	VertexBuffer::VertexBuffer()
		: m_ID(0)
	{
		GLCall(glGenBuffers(1, &m_ID));
	}

	VertexBuffer::VertexBuffer(const void* data, const unsigned int size, GLenum usage)
		: m_ID(0)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::SetData(const void* data, const unsigned int size, GLenum usage)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}


}