#include "Renderer2D.h"

#include <iostream>
#include <GLFW\glfw3.h>

namespace mb { namespace graphics {

	Renderer2D::Renderer2D(const Window& window)
		: m_BasicShader("./res/basic.vert", "./res/basic.frag"), view()
	{
		unsigned short m_Indices[6];
		m_Indices[0] = 0;
		m_Indices[1] = 1;
		m_Indices[2] = 2;
		m_Indices[3] = 2;
		m_Indices[4] = 3;
		m_Indices[5] = 0;

		m_IBO = new IndexBuffer(m_Indices, 3 * 2 * sizeof(unsigned short));

		proj = maths::ortho(-window.GetSize().x / 2, window.GetSize().x / 2, -window.GetSize().y / 2, window.GetSize().y / 2, -5, 5);
		//view = maths::translate(view, {0, 0, -2});

		//std::cout << proj << std::endl;
	}

	Renderer2D::~Renderer2D()
	{
		if(m_IBO)
			delete m_IBO;
	}

	void Renderer2D::Draw(const Sprite2D& sprite)
	{
		maths::Mat4 model;
		model = maths::translate(model, { sprite.transform.position, 0 });
		model = maths::scale(model, {sprite.transform.scale, 1});
		model = maths::rotate(model, sprite.transform.rotationAngle, sprite.transform.rotationAxis);

		m_BasicShader.Bind();
		m_BasicShader.SetUniform1i("textured", sprite.HasTexture());
		if(!sprite.HasTexture())
			m_BasicShader.SetUniformVec3("u_Color", sprite.GetColor());
		//m_BasicShader.SetUniformMat4("u_Model", model);
		//m_BasicShader.SetUniformMat4("u_View", view);
		//m_BasicShader.SetUniformMat4("u_Proj", proj);
		m_BasicShader.SetUniformMat4("u_MVP", proj * view * model);

		sprite.Bind();
		m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		/*GLenum err;
		while ((err = glGetError()))
		{
			std::cout << err << std::endl;
		}

		m_IBO->Unbind();
		sprite.Unbind();
		m_BasicShader.Unbind();*/
	}
} }