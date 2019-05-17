#include "Sandbox.h"

Sandbox::Sandbox()
{
	m_Window = new Window(1200, 800, "Hi");
	m_Window->QuitOnPress(Key::ESCAPE_KEY);
	m_Window->SetClearColor(Color::CYAN);
	m_Window->SetVsync(false);

	SystemManager::AddSystem(new coreSystems::RenderingSystem(m_Window->GetSize()));

	rm.AddTexture("./res/alien.png", 0);

	alien.AddComponent<RenderComponent>();
	alien.GetComponent<RenderComponent>()->sprite = Sprite2D({ 100, 100 });
	alien.GetComponent<RenderComponent>()->sprite.SetTexture(rm.GetTexture(0));
	alien.AddComponent<TransformComponent>();
	alien.GetComponent<TransformComponent>()->position = { 0, 0 };
}

Sandbox::~Sandbox()
{
}