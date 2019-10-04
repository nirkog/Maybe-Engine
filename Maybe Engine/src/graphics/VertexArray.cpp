#include "VertexArray.h"

namespace mb {

	unsigned int GetTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_INT:
			return sizeof(int);
			break;
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
			break;
		case GL_FLOAT:
			return sizeof(float);
			break;
		case GL_BYTE:
			return sizeof(char);
			break;
		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char);
			break;
		case GL_DOUBLE:
			return sizeof(double);
			break;
		case GL_SHORT:
			return sizeof(short);
			break;
		}
	}

	VertexArray::VertexArray()
	{
		GLCall(glCreateVertexArrays(1, &m_ID));
	}
	
	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_ID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

	void VertexArray::AddBuffer(const VertexBuffer& buffer)
	{
		Bind();
		buffer.Bind();
		const VertexBufferLayout& layout = buffer.GetLayout();
		const Array<VertexBufferLayout::BufferLayoutItem>& items = layout.GetItems();
		unsigned int offset = 0;

		for (auto it = items.Begin(), end = items.End(); it != end; it++)
		{
			VertexBufferLayout::BufferLayoutItem& item = (*it);

			GLCall(glEnableVertexAttribArray(item.index));
			GLCall(glVertexAttribPointer(item.index, item.count, item.type, item.normalized, layout.GetStride(), (const void*) offset));
			offset += item.count * GetTypeSize(item.type);
		}

		Unbind();
	}

	void VertexArray::AddBuffer(const IndexBuffer& buffer)
	{
		Bind();
		buffer.Bind();
		Unbind();
	}
	
}