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

#define TEST 1

int main()
{
	Init();

	Window window(WIDTH, HEIGHT, "Maybe This Will Work");
	window.QuitOnPress(ESCAPE_KEY);
	window.SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	window.SetVsync(false);

	Time::EnableFpsLog();
	LogOpenGLDetails();

	ResourceManager rm;

#if TEST
	SystemManager::AddSystem(new coreSystems::RenderingSystem(window));

	rm.AddTexture("./res/alien.png", "alien");
	rm.AddTexture("./res/smiley.png", "smiley");
	rm.AddTexture("./res/spaceship.png", "spaceship");
	rm.DeleteTexture("smiley");

	Entity alien;
	auto* renderComp = alien.AddComponent<RenderComponent>();
	renderComp->sprite = { { 100, 100 } };
	renderComp->sprite.SetTexture(rm.GetTexture("alien"));
	auto* transformComp = alien.AddComponent<TransformComponent>();
	transformComp->position = { 200, 0 };

	Entity spaceship;
	auto* spaceRender = spaceship.AddComponent<RenderComponent>();
	spaceRender->sprite = { { 100, 100 } };
	spaceRender->sprite.SetTexture(rm.GetTexture("spaceship"));
	auto* spaceTransform = spaceship.AddComponent<TransformComponent>();
	spaceTransform->position = { -200, 0 };

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