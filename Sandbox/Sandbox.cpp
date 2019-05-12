#include "Sandbox.h"

Sandbox::Sandbox() 
	: paddle1("PADDLE1"), paddle2("PADDLE2"), ball("BALL")
{
	m_Window = new Window(1200, 800, "Hi");
	m_Window->QuitOnPress(Key::ESCAPE_KEY);
	m_Window->SetClearColor("#111111");
	m_Window->SetVsync(false);

	Time::EnableFpsLog();

	rm.AddTexture("./res/alien.png", 0);

	SystemManager::AddSystem(new InputSystem());
	SystemManager::AddSystem(new MovementSystem(*m_Window));
	SystemManager::AddSystem(new coreSystems::RenderingSystem(m_Window->GetSize()));

	auto* renderComp = paddle1.AddComponent<RenderComponent>();
	renderComp->sprite = { { 15, 125 } };
	renderComp->sprite.SetColor("#fefefe");
	auto* transformComp = paddle1.AddComponent<TransformComponent>();
	transformComp->position = { -m_Window->GetSize().x / 2 + 20, 0 };
	auto* inputComp = paddle1.AddComponent<InputComponent>();
	inputComp->upKey = UP_KEY;
	inputComp->downKey = DOWN_KEY;
	auto* scoreComp = paddle1.AddComponent<ScoreComponent>();
	scoreComp->score = 0;

	auto* ballRenderComp = ball.AddComponent<RenderComponent>();
	ballRenderComp->sprite = { { 45, 45 } };
	ballRenderComp->sprite.SetTexture(rm.GetTexture(0));
	auto* ballTransformComp = ball.AddComponent<TransformComponent>();
	ballTransformComp->position = { 0, 0 };
	ballTransformComp->velocity = { 100, 350 };

	paddle1.Duplicate(&paddle2);
	paddle2.GetComponent<TransformComponent>()->position.x = m_Window->GetSize().x / 2 - 20;
	auto* inputComp2 = paddle2.GetComponent<InputComponent>();
	inputComp2->upKey = W_KEY;
	inputComp2->downKey = S_KEY;
}

Sandbox::~Sandbox()
{
	Log::Warn("Destroying sandbox!");
}