#include <iostream>

#include "maths\maths.h"
#include "graphics\graphics.h"
#include "utils\utils.h"
#include "input\input.h"
#include "platform\platform.h"
#include "physics\physics.h"
#include "Systems.h"

#define WIDTH 1200
#define HEIGHT 800

using namespace mb::graphics;
using namespace mb::utils;
using namespace mb::platform;
using namespace mb::maths;
using namespace mb::input;

#define TEST 0

int main()
{
	Init();

	Window window(WIDTH, HEIGHT, "Maybe This Will Work");
	window.QuitOnPress(ESCAPE_KEY);
	window.SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	window.SetVsync(false);

	Time::EnableFpsLog();
	LogOpenGLDetails();

#if TEST
	SystemManager::AddSystem(new coreSystems::RenderingSystem(window));

	Entity ball("BALL");
	auto* renderComp = ball.AddComponent<RenderComponent>();
	renderComp->sprite = { { 100, 100 } };
	renderComp->sprite.SetColor({ 0.95f, 0.25f, 0.12f });
	renderComp->sprite.SetDrawingMode(DrawingMode::PRIMITIVE);
	renderComp->sprite.SetShape(Shape::CIRCLE);
	renderComp->sprite.SetRadius(100);
	renderComp->sprite.SetCirclePrecision(3);
	auto* transformComp = ball.AddComponent<TransformComponent>();
	transformComp->position = { 125, 0 };
	transformComp->scale = { 1.5f, 1.5f};

	Entity ball2("BALL2");
	auto* renderComp2 = ball2.AddComponent<RenderComponent>();
	renderComp2->sprite = { { 20, 20 } };
	renderComp2->sprite.SetColor({ 0.95f, 0.25f, 0.12f });
	renderComp2->sprite.SetDrawingMode(DrawingMode::PRIMITIVE);
	renderComp2->sprite.SetShape(Shape::CIRCLE);
	renderComp2->sprite.SetRadius(100);
	renderComp2->sprite.SetCirclePrecision(250);
	auto* transformComp2 = ball2.AddComponent<TransformComponent>();
	transformComp2->position = { -300, 0 };
	transformComp2->scale = { 1.5f, 1.5f };

	while (window.Open())
	{
		Update(window);
		window.Clear();

		SystemManager::Update();

		window.Update();
	}

#else
	SystemManager::AddSystem(new InputSystem());
	SystemManager::AddSystem(new MovementSystem(window));
	SystemManager::AddSystem(new coreSystems::RenderingSystem(window));

	Entity paddle1("PADDLE1");
	auto* renderComp = paddle1.AddComponent<RenderComponent>();
	renderComp->sprite = { { 15, 125 } };
	renderComp->sprite.SetColor({ 0.95f, 0.95f, 0.95f });
	auto* transformComp = paddle1.AddComponent<TransformComponent>();
	transformComp->position = { -window.GetSize().x / 2 + 20, 0 };
	auto* inputComp = paddle1.AddComponent<InputComponent>();
	inputComp->upKey = UP_KEY;
	inputComp->downKey = DOWN_KEY;
	auto* scoreComp = paddle1.AddComponent<ScoreComponent>();
	scoreComp->score = 0;

	Entity ball("BALL");
	auto* ballRenderComp = ball.AddComponent<RenderComponent>();
	ballRenderComp->sprite = { { 30, 30 } };
	ballRenderComp->sprite.SetColor({ 0.9f, 0.9f, 0.9f });
	auto* ballTransformComp = ball.AddComponent<TransformComponent>();
	ballTransformComp->position = { 0, 0 };
	ballTransformComp->velocity = { 100, 350 };

	Entity paddle2("PADDLE2");
	paddle1.Duplicate(&paddle2);
	paddle2.GetComponent<TransformComponent>()->position.x = window.GetSize().x / 2 - 20;
	auto* inputComp2 = paddle2.GetComponent<InputComponent>();
	inputComp2->upKey = W_KEY;
	inputComp2->downKey = S_KEY;

	while (window.Open())
	{
		Update(window);
		window.Clear();

		SystemManager::Update();

		window.Update();
	}

#endif

	SystemManager::Destroy();

	return 0;
}