#pragma once

#include <vector>

#include "Buffer.h"

namespace mb { namespace graphics {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddBuffer(const Buffer& buffer);
		void AddBuffer(const Buffer* buffer);

		inline const unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
		static unsigned int m_ActiveArray;
		std::vector<Buffer> m_Buffers;
	};

} }