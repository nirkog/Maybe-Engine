#pragma once

#include "../core/Array.h"
#include "../core/math/mat4.h"
#include "GL.h"

namespace mb {

	class VertexBufferLayout
	{
	public:
		struct BufferLayoutItem
		{
			unsigned int index, count, type, normalized;
		};

		VertexBufferLayout()
			: m_Stride(0) {}

		template<typename T>
		void Push(unsigned int count)
		{
			m_Items.PushBack({ m_Items.Count(), count, GetGLType<T>(), GL_FALSE});
			m_Stride += count * sizeof(T);
		}

		inline unsigned int GetStride() const { return m_Stride; }
		inline const Array<BufferLayoutItem>& GetItems() const { return m_Items; }
	private:
		template<typename T>
		unsigned int GetGLType();

		template<>
		unsigned int GetGLType<int>() { return GL_INT; }

		template<>
		unsigned int GetGLType<unsigned int>() { return GL_UNSIGNED_INT; }

		template<>
		unsigned int GetGLType<float>() { return GL_FLOAT; }

		template<>
		unsigned int GetGLType<char>() { return GL_BYTE; }

		template<>
		unsigned int GetGLType<unsigned char>() { return GL_UNSIGNED_BYTE; }

		template<>
		unsigned int GetGLType<double>() { return GL_DOUBLE; }

		template<>
		unsigned int GetGLType<short>() { return GL_SHORT; }
	private:
		Array<BufferLayoutItem> m_Items;
		unsigned int m_Stride;
	};

}