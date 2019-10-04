#include "VertexArray.h"

#include <GL\glew.h>

namespace mb { namespace graphics {

	unsigned int VertexArray::m_ActiveArray = 0;

	VertexArray::VertexArray()
		: m_ID(0)
	{
		GLCall(glGenVertexArrays(1, &m_ID));
	}
	
	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}

	void VertexArray::Bind() const
	{
		if (m_ActiveArray != m_ID)
		{
			GLCall(glBindVertexArray(m_ID));
			m_ActiveArray = m_ID;
		}
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
		m_ActiveArray = 0;
	}

	void VertexArray::AddBuffer(const Buffer& buffer)
	{
		Bind();
		buffer.Bind();
		const BufferLayout layout = buffer.GetLayout();
		const std::vector<BufferLayoutItem> items = layout.GetItems();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < items.size(); i++)
		{
			BufferLayoutItem item = items[i];
			//std::cout << "Index: " << item.index << ", Count: " << item.count << ", Offset: " << offset << std::endl;

			GLCall(glEnableVertexAttribArray(item.index));
			GLCall(glVertexAttribPointer(item.index, item.count, item.type, item.normalized, layout.GetStride(), (const void*) offset));
			offset += item.count * GetTypeSize(item.type);
		}

		Unbind();

		//m_Buffers.push_back(buffer);
	}

	void VertexArray::AddBuffer(const Buffer* buffer)
	{
		Bind();
		buffer->Bind();
		const BufferLayout layout = buffer->GetLayout();
		const std::vector<BufferLayoutItem> items = layout.GetItems();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < items.size(); i++)
		{
			BufferLayoutItem item = items[i];
			//std::cout << "Index: " << item.index << ", Count: " << item.count << ", Offset: " << offset << std::endl;

			GLCall(glEnableVertexAttribArray(item.index));
			GLCall(glVertexAttribPointer(item.index, item.count, item.type, item.normalized, layout.GetStride(), (const void*)offset));
			offset += item.count * GetTypeSize(item.type);
		}

		Unbind();

		//m_Buffers.push_back(buffer);
	}

} }