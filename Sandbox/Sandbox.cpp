#include "Sandbox.h"

ExampleLayer::ExampleLayer()
	: timer(0), frames(0), clearColor(0.2f, 0.6f, 0.89f), color(1, 1, 1, 1)
{
	mb::RenderCommand::InitBlending();

	unsigned int fit = 50;

	size.x = 2.0f / (float) fit;
	size.y = 2.0f / (float) fit;

	positions.Reserve(mb::Math::Pow(fit, 2));
	colors.Reserve(mb::Math::Pow(fit, 2));

	for (unsigned int i = 0; i < fit; i++)
	{
		for (unsigned int j = 0; j < fit; j++)
		{
			positions.PushBack({ (size.x / 2 + size.x * j) - 1, (size.y / 2 + size.y * i) - 1, 0});
			colors.PushBack({ 
				(float) mb::Math::Rand(), 
				(float) mb::Math::Rand(),
				(float) mb::Math::Rand(),
				(float) mb::Math::Rand()
			});
		}
	}

	quadCount = positions.Count();

	mb::Log::Debug("Rendering {} Quads!", mb::Math::Pow(fit, 2));


	mb::RenderCommand::SetClearColor(clearColor);
}

ExampleLayer::~ExampleLayer()
{

}

void ExampleLayer::OnAttach()
{

}

void ExampleLayer::OnDetach()
{

}

void ExampleLayer::OnUpdate(float deltaTime)
{
	timer += deltaTime;
	frames++;

	if (timer >= 1.0f)
	{
		mb::Log::Debug("{} FPS", frames);

		timer = 0;
		frames = 0;
	}

	mb::RenderCommand::Clear();

	renderer.Begin();

	//renderer.Submit({ 1, 1 }, { 0, 0, 0 }, color);

	for(unsigned int i = 0; i < quadCount; i++)
	{
		renderer.Submit(size, positions[i], colors[i]);
	}

	renderer.End();

	/*shader.Bind();
	vao.Bind();

	mb::RenderCommand::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);*/
}

void ExampleLayer::OnEvent(mb::Event& e)
{
	if (e.GetType() == mb::EventType::MouseMovedEvent)
	{
		mb::MouseMovedEvent& me = (mb::MouseMovedEvent&) e;
		
		mb::Vec2 windowSize = mb::Application::GetInstance()->GetWindow().GetSize();
		mb::Vec2 xy = me.GetPosition() / windowSize;

		color.r = xy.x;
		color.g = xy.y;
		color.b = clearColor.z;
	}

	/*if (e.GetType() == mb::EventType::WindowResizeEvent)
	{
		mb::WindowResizeEvent& re = (mb::WindowResizeEvent&) e;

		mb::Log::Debug("Resizing to ({}, {})!", re.GetWidth(), re.GetHeight());
	}
	if (e.GetType() == mb::EventType::MouseButtonPressedEvent)
	{
		mb::Vec2 pos = mb::Input::GetMousePosition();

		mb::Log::Debug("Clicked! mouse position is {}!", pos);
	}
	else if (e.GetType() == mb::EventType::MouseEnterEvent)
	{
		mb::Log::Debug("Hey! Welcome Back!");
	}
	else if (e.GetType() == mb::EventType::MouseLeaveEvent)
	{
		mb::Log::Debug("Oh No! Come Back Soon!");
	}
	else if (e.GetType() == mb::EventType::MouseScrolledEvent)
	{
		mb::MouseScrolledEvent& se = (mb::MouseScrolledEvent&) e;

		mb::Log::Debug("Oh What a Scroll! The Offset is {}!", se.GetOffset());
	}
	else if (e.GetType() == mb::EventType::KeyPressedEvent)
	{
		mb::KeyPressedEvent& pe = (mb::KeyPressedEvent&) e;

		if(pe.GetKeyCode() == mb::KeyCode::KEY_S && pe.HasMod(mb::KeyMod::CONTROL))
			mb::Log::Debug("SAVE!!!!");
	}
	else if (e.GetType() == mb::EventType::KeyReleasedEvent)
	{
		mb::KeyReleasedEvent& re = (mb::KeyReleasedEvent&) e;

		if (re.GetKeyCode() == mb::KeyCode::KEY_A) mb::Log::Debug("WOOHA! YOU RELEASED A!");
	}*/
}