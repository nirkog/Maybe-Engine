#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "maths\maths.h"
#include "graphics\graphics.h"
#include "utils\utils.h"
#include "input\input.h"

mb::maths::Vec3 clearColor(0.1f, 0.7f, 0.34f);

int main()
{
	srand((unsigned int) time(NULL));
	mb::utils::Init();

	mb::graphics::Window window(800, 600, "Maybe This Will Work");

	window.QuitOnPress(GLFW_KEY_ESCAPE);

	mb::utils::EnableFpsLog();

	mb::graphics::Renderer2D renderer(window);

	mb::graphics::Sprite2D sprite({ 0, 0 }, { 200, 200 });
	sprite.SetColor({0.5f, 0.25f, 0.75f});

	while (window.Open())
	{
		mb::utils::Update(window);
		window.Clear(clearColor.x, clearColor.y, clearColor.z, 1.0f);

		sprite.transform.position.x = (float)sin(2 * (float)glfwGetTime()) * 200;

		renderer.Draw(sprite);

		window.Update();
	}

	mb::utils::Terminate();

	//std::cin.get();

	return 0;
}