#include "Texture.h"

namespace mb {

	Texture::Texture(const char* path)
		: m_Width(0), m_Height(0), m_ID(0)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
		m_Width = (unsigned int) width;
		m_Height = (unsigned int) height;

		ASSERT(data, "Unable to load texture!");

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 3)
		{
			dataFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else if (channels == 4)
		{
			dataFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}

		ASSERT(dataFormat & internalFormat, "Texture format is not supported!");

		GLCall(glGenTextures(1, &m_ID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data));
	
		stbi_image_free(data);
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
}