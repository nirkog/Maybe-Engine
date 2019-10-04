#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace mb {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddBuffer(const VertexBuffer& buffer);
		void AddBuffer(const IndexBuffer& buffer);

		inline const unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
	};

}