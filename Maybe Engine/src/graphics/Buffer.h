#pragma once

#include "BufferLayout.h"

namespace mb { namespace graphics {

	class Buffer
	{
	public:
		Buffer(const void* data, const unsigned int size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		void SetLayout(BufferLayout& layout);

		inline unsigned int GetID() const { return m_ID; }
		inline const BufferLayout& GetLayout() const { return m_Layout; }
	private:
		unsigned int m_ID;
		BufferLayout m_Layout;
	};

} }