#pragma once

namespace mb { namespace graphics {

	class Texture
	{
	public:
		Texture(const char* path);
		Texture();
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline const char* GetSource() const { return m_Path; }
	private:
		unsigned int m_ID;
		char* m_Path;
		int m_Width, m_Height, m_BPP;
	};

} }