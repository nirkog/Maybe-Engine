#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

#include "maths\maths.h"
#include "graphics\graphics.h"
#include "utils\utils.h"
#include "input\input.h"
#include "platform\platform.h"

#define WIDTH 1200
#define HEIGHT 800

using namespace mb::graphics;
using namespace mb::utils;
using namespace mb::platform;
using namespace mb::maths;
using namespace mb::input;

int main()
{
	srand((unsigned int) time(NULL));
	Init();

	Window window(WIDTH, HEIGHT, "Maybe This Will Work");
	window.QuitOnPress(GLFW_KEY_ESCAPE);

	Time::EnableFpsLog();
	std::cout << glGetString(GL_RENDERER) << std::endl;

	Vec4 clearColor(0.2f, 0.6f, 0.75f, 1.0f);

	BatchRenderer renderer(window);

	Texture spaceshipTexture("./res/spaceship.png");
	Texture alienTexture("./res/alien.png");

	SystemManager::AddSystem(new MovementSystem());

	float gravity = 275.0f;

	Sprite2D playerSprite({ 0, -300 }, {100, 100}); 
	playerSprite.SetTexture(&alienTexture);

	Entity player;
	auto* playerTransform = player.AddComponent<TransformComponent>();
	playerTransform->position = {0, -200};
	auto* playerRender = player.AddComponent<RenderComponent>();
	playerRender->sprite = playerSprite;

	SystemManager::Init();

	while (window.Open())
	{
		Update(window);
		window.Clear(clearColor);

		if (Input::IsKeyDown(SPACE_KEY) && playerTransform->velocity.y == 0)
		{
			playerTransform->velocity = { 0, 300 };
		}

		SystemManager::Update();

		renderer.Begin();

		renderer.Submit(playerRender, playerTransform);

		renderer.End();

		window.Update();
	}

	SystemManager::Destroy();

	return 0;
}