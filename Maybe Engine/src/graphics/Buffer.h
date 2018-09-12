#pragma once

namespace mb { namespace graphics {

	class Buffer
	{
	public:
		Buffer(const void* data, const unsigned int size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetID() const { return m_ID; }

	private:
		unsigned int m_ID;
	};

} }