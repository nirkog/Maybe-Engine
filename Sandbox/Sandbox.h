#pragma once

#include "core/Log.h"
#include "core/Color.h"
#include "core/math/math_funcs.h"
#include "graphics/RenderCommand.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/Texture.h"
#include "graphics/Renderer.h"
#include "Application.h"

#include "Input.h"

class ExampleLayer : public mb::Layer
{
public:
	ExampleLayer();
	~ExampleLayer();

	void OnAttach();
	void OnDetach();

	void OnUpdate(float deltaTime);

	void OnEvent(mb::Event& event);
private:
	mb::Renderer renderer;

	mb::Color color;
	mb::Vec3 clearColor;

	mb::Vec2 size;
	mb::Array<mb::Vec3> positions;
	mb::Array<mb::Color> colors;

	float timer;
	unsigned int frames;

	unsigned int quadCount;
};

class SandboxApplication : public mb::Application
{
public:
	SandboxApplication()
	{
		SetCloseOnEscape(true);

		m_LayerStack.PushLayer(new ExampleLayer());
	}

	~SandboxApplication()
	{

	}
};