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

mb::maths::Vec3 clearColor(0.8f, 0.45f, 0.3f);

int main()
{
	srand((unsigned int) time(NULL));
	mb::utils::Init();

	mb::graphics::Window window(800 * 1.5f, 450 * 1.5f, "Maybe This Will Work");

	window.QuitOnPress(GLFW_KEY_ESCAPE);

	mb::graphics::Renderer2D renderer(window);
	mb::graphics::BatchRenderer batch(window);

	mb::utils::EnableFpsLog();
	mb::graphics::Sprite2D sprite({ 0, 0 }, { 200, 200 });
	sprite.SetColor({0.0f, 0.2f, 0.9f});
	sprite.SetTexture("./res/smiley.png");

	//batch.Submit(sprite);

	bool renderBoth = true;

	float fr = 1.5f;

	while (window.Open())
	{
		mb::utils::Update(window);
		window.Clear(clearColor.x, clearColor.y, clearColor.z, 1.0f);

		if (mb::input::IsKeyDown(mb::input::Key::Y))
			renderBoth = !renderBoth;

		if (mb::input::IsKeyPressed(mb::input::Key::UP))
			fr += mb::utils::deltaTime;
		else if (mb::input::IsKeyPressed(mb::input::Key::DOWN))
			fr -= mb::utils::deltaTime;

		sprite.transform.position.x = (float) sin(fr * (float)glfwGetTime()) * 300;
		sprite.transform.rotationAngle += mb::maths::radians(270) * mb::utils::deltaTime;
		sprite.transform.scale.x = 1 + (float)sin(3 * (float)glfwGetTime()) * 0.1f;
		sprite.transform.scale.y = 1 + (float)sin(3 * (float)glfwGetTime()) * 0.1f;

		batch.Submit(sprite);
		batch.Flush();

		/*renderer.Draw(sprite);
		
		sprite.transform.position.x = (float) sin(fr * (float)glfwGetTime() + mb::maths::radians(180)) * 300;

		if(renderBoth)
			renderer.Draw(sprite);*/

		window.Update();
	}

	mb::utils::Terminate();

	//std::cin.get();

	return 0;
}