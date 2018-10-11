#include "Texture.h"

#include <iostream>
#include <GL\glew.h>
#include "stb_image.h"

namespace mb { namespace graphics {

	Texture::Texture(const char* path)
		: m_ID(0), m_Width(0), m_Height(0), m_BPP(0), m_Data(nullptr)
	{
		stbi_set_flip_vertically_on_load(1);
		m_Path = (char*) path;
		m_Data = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		if (m_Data)
			stbi_image_free(m_Data);
		else
			std::cout << "Error" << std::endl;
	}

	Texture::Texture()
		: m_ID(0), m_Width(0), m_Height(0), m_BPP(0), m_Data(nullptr)
	{

	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		//std::cout << m_ID << std::endl;
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

} }