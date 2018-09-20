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

void changeBackgroundColor()
{
	float r = (float) rand() / RAND_MAX;
	float g = (float) rand() / RAND_MAX;
	float b = (float) rand() / RAND_MAX;

	clearColor = {r, g, b};
}

int main()
{
	srand((unsigned int) time(NULL));
	mb::utils::Init();

	mb::graphics::Window window(800, 600, "Maybe This Will Work");
	glfwSwapInterval(0);

	window.QuitOnPress(GLFW_KEY_ESCAPE);

	mb::graphics::Renderer2D renderer(window);

	mb::graphics::Sprite2D sprite({ 400, 0 }, {300, 100});

	mb::maths::Vec3 color(0.4f, 0.4f, 0.8f);

	float frequency = 1.0f;

	//std::cout << mb::maths::translate(mb::maths::Mat4(), { 0.5f, 0.5f, 0 });

	while (window.Open())
	{
		mb::utils::Update(window);
		window.Clear(clearColor.x, clearColor.y, clearColor.z, 1.0f);

		if (mb::input::IsKeyReleased(mb::input::Key::J))
			changeBackgroundColor();

		if (mb::input::IsKeyPressed(mb::input::Key::UP))
			frequency += 0.25f * mb::utils::deltaTime;
		else if (mb::input::IsKeyPressed(mb::input::Key::DOWN))
			frequency -= 0.25f * mb::utils::deltaTime;

		color.z = abs(sin(frequency * (float) glfwGetTime()));
		color.x = abs(cos(3 * frequency * (float) glfwGetTime())) / 2;

		sprite.SetColor(color);
		renderer.Draw(sprite);

		window.Update();
	}

	mb::utils::Terminate();

	//std::cin.get();

	return 0;
}