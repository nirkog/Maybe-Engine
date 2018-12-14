#pragma once

#include <vector>

#include "GL.h"
#include "..\maths\maths.h"

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

		template<>
		inline void Push<float>(unsigned int count)
		{
			m_Items.push_back({ m_Items.size(), count, GL_FLOAT, GL_FALSE });
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
	private:
		std::vector<BufferLayoutItem> m_Items;
		unsigned int m_Stride;
	};

} }