#pragma once

namespace mb { namespace graphics {

	class IndexBuffer
	{
	public:
		IndexBuffer(const void* data, const unsigned int size);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline const unsigned int GetId() const { return m_ID; }
	private:
		unsigned int m_ID;
	};

} }