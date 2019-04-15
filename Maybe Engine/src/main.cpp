//#include <iostream>
//
//#include "maths\maths.h"
//#include "graphics\graphics.h"
//#include "utils\utils.h"
//#include "input\input.h"
//#include "platform\platform.h"
//#include "physics\physics.h"
//#include "Systems.h"
//
//#define WIDTH 1200
//#define HEIGHT 800
//
//using namespace mb::graphics;
//using namespace mb::utils;
//using namespace mb::platform;
//using namespace mb::maths;
//using namespace mb::input;
//
//int main()
//{
//	Init();
//
//	Window window(WIDTH, HEIGHT, "Maybe This Will Work");
//	window.QuitOnPress(ESCAPE_KEY);
//	window.SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//	window.SetVsync(false);
//
//	Time::EnableFpsLog();
//	LogOpenGLDetails();
//
//	SystemManager::AddSystem(new InputSystem());
//	SystemManager::AddSystem(new MovementSystem(window));
//	SystemManager::AddSystem(new coreSystems::RenderingSystem(window));
//
//	Entity paddle1("PADDLE1");
//	auto* renderComp = paddle1.AddComponent<RenderComponent>();
//	renderComp->sprite = { { 15, 125 } };
//	renderComp->sprite.SetColor({ 0.95f, 0.95f, 0.95f });
//	auto* transformComp = paddle1.AddComponent<TransformComponent>();
//	transformComp->position = { -window.GetSize().x / 2 + 20, 0 };
//	auto* inputComp = paddle1.AddComponent<InputComponent>();
//	inputComp->upKey = UP_KEY;
//	inputComp->downKey = DOWN_KEY;
//	auto* scoreComp = paddle1.AddComponent<ScoreComponent>();
//	scoreComp->score = 0;
//
//	Entity paddle2("PADDLE2");
//	paddle1.Duplicate(&paddle2);
//	paddle2.GetComponent<TransformComponent>()->position.x = window.GetSize().x / 2 - 20;
//	auto* inputComp2 = paddle2.GetComponent<InputComponent>();
//	inputComp2->upKey = W_KEY;
//	inputComp2->downKey = S_KEY;
//
//	Entity ball("BALL");
//	auto* ballRenderComp = ball.AddComponent<RenderComponent>();
//	ballRenderComp->sprite = { { 30, 30 } };
//	ballRenderComp->sprite.SetColor({ 0.9f, 0.9f, 0.9f });
//	auto* ballTransformComp = ball.AddComponent<TransformComponent>();
//	ballTransformComp->position = { 0, 0 };
//	ballTransformComp->velocity = { 100, 350 };
//
//	while (window.Open())
//	{
//		Update(window);
//		window.Clear();
//
//		SystemManager::Update();
//
//		window.Update();
//	}
//
//	SystemManager::Destroy();
//
//	return 0;
//}