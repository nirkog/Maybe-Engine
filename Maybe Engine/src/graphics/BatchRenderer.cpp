#include "BatchRenderer.h"

#include <sstream>

#define MAX_SPRITES 60000
#define VERTEX_SIZE sizeof(float) * 9
#define BUFFER_SIZE VERTEX_SIZE * 4 * MAX_SPRITES
#define INDICES_SIZE MAX_SPRITES * 6
#define INDEX_BUFFER_SIZE INDICES_SIZE * sizeof(unsigned int)

namespace mb { namespace graphics {

	BatchRenderer::BatchRenderer(const Window& window)
		: m_VBO(0), m_VAO(0), m_IBO(0), m_Shader("./res/batcher.vert", "./res/batcher.frag"), m_SpriteCount(0), m_TextureCount(0), m_View(1), m_Proj(1), window(window)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) (5 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const void*) (6 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		unsigned int* indices = new unsigned int[INDICES_SIZE];
		unsigned int offset = 0;

		for (unsigned int i = 0; i < INDICES_SIZE; i += 6)
		{
			indices[  i  ] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_BUFFER_SIZE, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete indices;

		m_Proj = maths::Mat4::ortho(-window.GetSize().x / 2, window.GetSize().x / 2, -window.GetSize().y / 2, window.GetSize().y / 2, -5, 5);

		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_View", m_View);
		m_Shader.SetUniformMat4("u_Proj", m_Proj);

		GLenum err;
		while (err = glGetError())
		{
			std::cout << err;
		}

		defaultUV[0] = {0, 0};
		defaultUV[1] = {0, 1};
		defaultUV[2] = {1, 1};
		defaultUV[3] = {1, 0};
	}

	void BatchRenderer::Begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer::Submit(const Sprite2D* sprite)
	{
		const maths::Vec2& size = sprite->GetSize();
		const maths::Vec3& color = sprite->GetColor();
		const maths::Vec2& position = sprite->transform.position;
		unsigned int tid = 0;
		bool existingTexture = false;

		for (unsigned int i = 0; i < m_TextureCount; i++)
		{
			if (sprite->GetTexturePath() == m_BoundTextures[i].GetSource())
			{
				tid = i;
				existingTexture = true;
			}
		}

		if (!existingTexture)
		{
			m_BoundTextures[m_TextureCount] = *sprite->GetTexture();
			tid = m_TextureCount;
			m_TextureCount++;

			//std::cout << sprite->GetTexture()->GetSource() << " " << (float)tid / 32.0f;
			//std::cout << std::endl;
		}

		const float realTID = (float)tid / 32.0f;
		

		//m_Buffer->position = { -size.x / 2 + position.x, -size.y / 2 + position.y , 0 };
		m_Buffer->positionX = -size.x / 2 + position.x;
		m_Buffer->positionY = -size.x / 2 + position.y;
		m_Buffer->color = color;
		m_Buffer->uv = defaultUV[0];
		m_Buffer->tid = realTID;
		m_Buffer++;

		//m_Buffer->position = { -size.x / 2 + position.x, size.y / 2 + position.y, 0 };
		m_Buffer->positionX = -size.x / 2 + position.x;
		m_Buffer->positionY = size.y / 2 + position.y;
		m_Buffer->color = color;
		m_Buffer->uv = defaultUV[1];
		m_Buffer->tid = realTID;
		m_Buffer++;

		//m_Buffer->position = { size.x / 2 + position.x, size.y / 2 + position.y, 0 };
		m_Buffer->positionX = size.x / 2 + position.x;
		m_Buffer->positionY = size.y / 2 + position.y;
		m_Buffer->color = color;
		m_Buffer->uv = defaultUV[2];
		m_Buffer->tid = realTID;
		m_Buffer++;

		//m_Buffer->position = { size.x / 2 + position.x, -size.y / 2 + position.y, 0 };
		m_Buffer->positionX = size.x / 2 + position.x;
		m_Buffer->positionY = -size.y / 2 + position.y;
		m_Buffer->color = color;
		m_Buffer->uv = defaultUV[3];
		m_Buffer->tid = realTID;
		m_Buffer++;

		m_SpriteCount++;
	}

	void BatchRenderer::End()
	{
		//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		Flush();
	}

	void BatchRenderer::Flush()
	{
		/*VertexData data;
		glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(VertexData) * 3, sizeof(VertexData), &data);*/

		double xpos, ypos;
		glfwGetCursorPos((GLFWwindow*) window.GetGLFWwindow(), &xpos, &ypos);

		m_Shader.Bind();
		m_Shader.SetUniformVec2("u_LightCenter", {(float) (xpos / window.GetSize().x) * 2 - 1, (float) (abs(ypos - window.GetSize().y) / window.GetSize().y) * 2 - 1 });

		for (unsigned int i = 0; i < m_TextureCount; i++)
		{
			std::stringstream ss;
			ss << "u_Textures[" << i << "]";
			m_BoundTextures[i].Bind(i);
			m_Shader.SetUniform1i(ss.str(), i);
		}

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		GLenum err;
		while (err = glGetError())
		{
			std::cout << err;
		}

		glDrawElements(GL_TRIANGLES, 6 * m_SpriteCount, GL_UNSIGNED_INT, NULL);

		m_SpriteCount = 0;
		m_TextureCount = 0;

		while (err = glGetError())
		{
			std::cout << err;
		}
	}

	BatchRenderer::~BatchRenderer()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_IBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

} }