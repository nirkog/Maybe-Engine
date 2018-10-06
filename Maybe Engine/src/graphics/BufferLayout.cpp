#include "BufferLayout.h"

namespace mb { namespace graphics {

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

	template<>
	inline void BufferLayout::Push<float>(unsigned int count)
	{
		m_Items.push_back({ m_Items.size(), count, GL_FLOAT, GL_FALSE });
		m_Stride += count * GetTypeSize(GL_FLOAT);
	}

	template<>
	inline void BufferLayout::Push<unsigned int>(unsigned int count)
	{
		m_Items.push_back({ m_Items.size(), count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += count * GetTypeSize(GL_UNSIGNED_INT);
	}

	template<>
	inline void BufferLayout::Push<int>(unsigned int count)
	{
		m_Items.push_back({ m_Items.size(), count, GL_INT, GL_FALSE });
		m_Stride += count * GetTypeSize(GL_INT);
	}

	template<>
	inline void BufferLayout::Push<unsigned char>(unsigned int count)
	{
		m_Items.push_back({ m_Items.size(), count, GL_UNSIGNED_BYTE, GL_FALSE });
		m_Stride += count * GetTypeSize(GL_UNSIGNED_BYTE);
	}

} }