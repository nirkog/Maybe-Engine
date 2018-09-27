#include "BatchRenderer.h"

#include "BufferLayout.h"

#define MAX_SPRITES 100
#define BUFFER_SIZE sizeof(float) * (4 + 3) * MAX_SPRITES
#define INDICES_SIZE MAX_SPRITES * 6

namespace mb { namespace graphics {

	BatchRenderer::BatchRenderer(const Window& window)
		: m_View(1), m_Proj(1), m_Shader("./res/batcher.vert", "./res/batcher.frag"), m_SpriteCount(0)
	{
		BufferLayout layout;
		layout.Push<float>(4);
		layout.Push<float>(3);

		m_Buffer = new Buffer(NULL, BUFFER_SIZE);
		m_Buffer->SetLayout(layout);

		unsigned short indices[INDICES_SIZE];
		unsigned short offset = 0;
		for (unsigned int i = 0; i < INDICES_SIZE; i+=6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
							 
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IndexBuffer = new IndexBuffer(indices, sizeof(unsigned short) * INDICES_SIZE);

		m_VertexArray = new VertexArray();
		m_VertexArray->AddBuffer(m_Buffer);

		m_Buffer->Bind();
		m_BufferPointer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		m_Buffer->Unbind();

		m_Proj = maths::ortho(-window.GetSize().x / 2, window.GetSize().x / 2, -window.GetSize().y / 2, window.GetSize().y / 2, -5, 5);
	}

	BatchRenderer::~BatchRenderer()
	{
		m_Buffer->Bind();
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_Buffer->Unbind();

		delete m_Buffer;
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

	void BatchRenderer::Submit(const Sprite2D& sprite)
	{
		const maths::Vec2 size = sprite.GetSize();
		const maths::Vec3 color = sprite.GetColor();

		maths::Mat4 model;
		model = maths::translate(model, maths::Vec3(sprite.transform.position, 0));
		model = maths::scale(model, maths::Vec3(sprite.transform.scale, 1));
		model = maths::rotate(model, sprite.transform.rotationAngle, sprite.transform.rotationAxis);

		m_BufferPointer->position = maths::Vec4(-size.x / 2, -size.y / 2, 0, 1) * model;
		m_BufferPointer->color = color;
		m_BufferPointer++;

		m_BufferPointer->position = maths::Vec4(-size.x / 2, size.y / 2, 0, 1) * model;
		m_BufferPointer->color = color;
		m_BufferPointer++;

		m_BufferPointer->position = maths::Vec4(size.x / 2, size.y / 2, 0, 1) * model;
		m_BufferPointer->color = color;
		m_BufferPointer++;

		m_BufferPointer->position = maths::Vec4(size.x / 2, -size.y / 2, 0, 1) * model;
		m_BufferPointer->color = color;
		m_BufferPointer++;

		m_SpriteCount++;
	}

	void BatchRenderer::Flush()
	{
		m_Buffer->Bind();
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_Buffer->Unbind();

		m_Shader.Bind();
		m_Shader.SetUniformMat4("u_View", m_View);
		m_Shader.SetUniformMat4("u_Proj", m_Proj);

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();

		glDrawElements(GL_TRIANGLES, m_SpriteCount * 6, GL_UNSIGNED_SHORT, 0);

		m_Shader.Unbind();
		m_VertexArray->Unbind();
		m_IndexBuffer->Unbind();

		m_SpriteCount = 0;

		m_Buffer->Bind();
		m_BufferPointer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		m_Buffer->Unbind();

		GLenum err;
		while ((err = glGetError()))
		{
			std::cout << err << std::endl;
		}
	}

} }