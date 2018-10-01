#pragma once

namespace mb { namespace graphics {

	class Texture
	{
	public:
		Texture(const char* path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;
	private:
		unsigned int m_ID;
		char* m_Path;
		unsigned char* m_Data;
		int m_Width, m_Height, m_BPP;
	};

} }