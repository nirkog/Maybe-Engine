#pragma once

#include "GL.h"

namespace mb {

	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(const void* data, const unsigned int size);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, const unsigned int size);

		inline const unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
	};

}