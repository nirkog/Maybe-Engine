#pragma once

#include "stb_image.h"

#include "GL.h"

namespace mb {

	class Texture
	{
	public:
		Texture(const char* path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline const unsigned int GetWidth() const { return m_Width; }
		inline const unsigned int GetHeight() const { return m_Height; }

		inline const unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_Width, m_Height;
		unsigned m_ID;
	};

}