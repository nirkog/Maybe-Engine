#include "Sandbox.h"

Sandbox::Sandbox()
{
	m_Window = new Window(1200, 800, "Hi");
	m_Window->QuitOnPress(Key::ESCAPE_KEY);
	m_Window->SetClearColor(Color::CYAN);
	m_Window->SetVsync(false);

	LogOpenGLDetails();

	SystemManager::AddSystem(new coreSystems::RenderingSystem(m_Window->GetSize()));

	rm.AddTexture("./res/alien.png", 0);

	rm.AddSound("./res/sound.wav", 0);
	rm.LoadSound(0);

	alien.AddComponent<RenderComponent>();
	alien.GetComponent<RenderComponent>()->sprite = Sprite2D({ 100, 100 });
	alien.GetComponent<RenderComponent>()->sprite.SetTexture(rm.GetTexture(0));
	alien.AddComponent<TransformComponent>();
	alien.GetComponent<TransformComponent>()->position = { 0, 0 };

	player.Play(*rm.GetSound(0));
}

Sandbox::~Sandbox()
{
}