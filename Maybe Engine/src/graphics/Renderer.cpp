#include "Renderer.h"

#define MAX_SPRITES 15000
#define VERTEX_BUFFER_SIZE sizeof(Renderer::VertexData) * 4 * MAX_SPRITES
#define INDICES_COUNT MAX_SPRITES * 6
#define INDEX_BUFFER_SIZE INDICES_COUNT * sizeof(unsigned int)

namespace mb {

	Renderer::Renderer()
		: m_VBOPointer(nullptr), m_Shader("./res/new.vert", "./res/new.frag"), m_SpriteCount(0)
	{
		m_VBOLayout.Push<float>(3);
		m_VBOLayout.Push<float>(4);

		m_VBO.SetData(NULL, VERTEX_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		m_VBO.SetLayout(m_VBOLayout);

		//std::unique_ptr<unsigned int> indices = std::make_unique<unsigned int>();
		unsigned int* indices = new unsigned int[INDICES_COUNT];
		unsigned int offset = 0;

		for (unsigned int i = 0; i < INDICES_COUNT; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO.SetData(indices, INDEX_BUFFER_SIZE);

		delete indices;

		m_VAO.AddBuffer(m_VBO);
		m_VAO.AddBuffer(m_IBO);
	}

	void Renderer::Begin()
	{
		m_VBO.Bind();
		GLCall(m_VBOPointer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void Renderer::End()
	{
		m_VBO.Bind();
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		Flush();
	}

	void Renderer::Submit(const Vec2& size, const Vec3& position, const Vec4& color)
	{
		/*Vec3 vertices[4] = {
			{ position.x - size.x / 2, position.y - size.y / 2, position.z },
			{ position.x - size.x / 2, position.y + size.y / 2, position.z },
			{ position.x + size.x / 2, position.y + size.y / 2, position.z },
			{ position.x + size.x / 2, position.y - size.y / 2, position.z}
		};

		for (unsigned char i = 0; i < 4; i++)
		{
			m_VBOPointer->position = vertices[i];
			m_VBOPointer->color = color;
			m_VBOPointer++;
		}*/

		m_VBOPointer->position = { position.x - size.x / 2, position.y - size.y / 2, position.z };
		m_VBOPointer->color = color;
		m_VBOPointer++;

		m_VBOPointer->position = { position.x - size.x / 2, position.y + size.y / 2, position.z };
		m_VBOPointer->color = color;
		m_VBOPointer++;

		m_VBOPointer->position = { position.x + size.x / 2, position.y + size.y / 2, position.z };
		m_VBOPointer->color = color;
		m_VBOPointer++;

		m_VBOPointer->position = { position.x + size.x / 2, position.y - size.y / 2, position.z };
		m_VBOPointer->color = color;
		m_VBOPointer++;

		m_SpriteCount++;
	}

	void Renderer::Flush()
	{
		m_Shader.Bind();
		m_VAO.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6 * m_SpriteCount, GL_UNSIGNED_INT, NULL));

		m_SpriteCount = 0;
	}

}