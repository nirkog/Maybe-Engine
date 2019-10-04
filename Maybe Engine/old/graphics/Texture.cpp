#include "Texture.h"

#include <iostream>
#include "GL.h"
#include "stb_image.h"

namespace mb { namespace graphics {

	Texture::Texture(const char* path)
		: m_ID(0), m_Width(0), m_Height(0), m_BPP(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_Path = (char*) path;
		unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);

		GLCall(glGenTextures(1, &m_ID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		//glGenerateMipmap(GL_TEXTURE_2D);

		if (data)
			stbi_image_free(data);
		else
			std::cout << "Error" << std::endl;
	}

	Texture::Texture()
		: m_ID(0), m_Width(0), m_Height(0), m_BPP(0)
	{

	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_ID));
	}

	void Texture::Bind(unsigned int slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

} }