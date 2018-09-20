#include "VertexArray.h"

#include <GL\glew.h>

namespace mb { namespace graphics {

	VertexArray::VertexArray()
		: m_ID(0)
	{
		glGenVertexArrays(1, &m_ID);
	}
	
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
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

			glEnableVertexAttribArray(item.index);
			glVertexAttribPointer(item.index, item.count, item.type, item.normalized, layout.GetStride(), (const void*) offset);
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

			glEnableVertexAttribArray(item.index);
			glVertexAttribPointer(item.index, item.count, item.type, item.normalized, layout.GetStride(), (const void*)offset);
			offset += item.count * GetTypeSize(item.type);
		}

		Unbind();

		//m_Buffers.push_back(buffer);
	}

} }