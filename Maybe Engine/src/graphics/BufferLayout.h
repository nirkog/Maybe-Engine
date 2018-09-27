#pragma once

#include <vector>
#include <iostream>

#include <GL\glew.h>

#include "..\maths\maths.h"

#define DEBUG 1

namespace mb { namespace graphics {

	struct BufferLayoutItem
	{
		unsigned int index, count, type, normalized;
	};

	unsigned int GetTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_FLOAT_MAT4:
			return sizeof(float) * 4 * 4;
		}

		return 0;
	}

	class BufferLayout
	{
	public:
		inline BufferLayout()
			: m_Stride(0)
		{
		}
		//~BufferLayout();

		template<typename T>
		void Push(unsigned int count)
		{

		}

		template<>
		inline void Push<float>(unsigned int count)
		{
			m_Items.push_back({m_Items.size(), count, GL_FLOAT, GL_FALSE});
			m_Stride += count * GetTypeSize(GL_FLOAT);
		}

		template<>
		inline void Push<unsigned int>(unsigned int count)
		{
			m_Items.push_back({ m_Items.size(), count, GL_UNSIGNED_INT, GL_FALSE });
			m_Stride += count * GetTypeSize(GL_UNSIGNED_INT);
		}

		template<>
		inline void Push<int>(unsigned int count)
		{
			m_Items.push_back({ m_Items.size(), count, GL_INT, GL_FALSE });
			m_Stride += count * GetTypeSize(GL_INT);
		}

		template<>
		inline void Push<unsigned char>(unsigned int count)
		{
			m_Items.push_back({ m_Items.size(), count, GL_UNSIGNED_BYTE, GL_FALSE });
			m_Stride += count * GetTypeSize(GL_UNSIGNED_BYTE);
		}

		inline unsigned int GetStride() const { return m_Stride; }
		inline const std::vector<BufferLayoutItem> GetItems() const { return m_Items; }

#if DEBUG
		inline void PrintLayout() const
		{
			for (unsigned int i = 0; i < m_Items.size(); i++)
			{
				BufferLayoutItem item = m_Items[i];
				std::cout << "Index: " << item.index << ", Type: " << GLTypeToString(item.type) << ", Count: " << item.count << std::endl;
			}
			std::cout << "Stride: " << m_Stride << std::endl;
		}

		inline const char* GLTypeToString(unsigned int type) const
		{
			switch (type)
			{
			case GL_FLOAT:
				return "float";
			case GL_INT:
				return "int";
			case GL_UNSIGNED_INT:
				return "unsigned int";
			case GL_UNSIGNED_BYTE:
				return "byte";
			}
		
			return "Unknown Type!";
		}
#endif
	private:
		std::vector<BufferLayoutItem> m_Items;
		unsigned int m_Stride;
	};

} }