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

	extern unsigned int GetTypeSize(unsigned int type);

	class BufferLayout
	{
	public:
		inline BufferLayout()
			: m_Stride(0)
		{
		}
		//~BufferLayout();

		template<typename T>
		void Push(unsigned int count);

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