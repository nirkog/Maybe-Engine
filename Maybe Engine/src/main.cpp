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

int main()
{
	srand((unsigned int) time(NULL));
	mb::utils::Init();

	mb::graphics::Window window(800 * 1.5f, 450 * 1.5f, "Maybe This Will Work");

	window.QuitOnPress(GLFW_KEY_ESCAPE);

	mb::utils::EnableFpsLog();

	std::cout << glGetString(GL_RENDERER) << std::endl;

	mb::graphics::BatchRenderer batch(window);

	mb::maths::Vec2 spriteSize = {3.8f, 3.8f};
	unsigned int spriteCount = 0;

	for (float x = -window.GetSize().x / 2 + spriteSize.x / 2; x < window.GetSize().x / 2; x += spriteSize.x)
	{
		for (float y = -window.GetSize().y / 2 + spriteSize.y / 2; y < window.GetSize().y / 2; y += spriteSize.y)
		{
			spriteCount++;
		}
	}

	mb::graphics::Sprite2D** sprites = (mb::graphics::Sprite2D**) malloc(sizeof(mb::graphics::Sprite2D) * spriteCount);
	unsigned int index = 0;

	for (float x = -window.GetSize().x / 2 + spriteSize.x / 2; x < window.GetSize().x / 2; x += spriteSize.x)
	{
		for (float y = -window.GetSize().y / 2 + spriteSize.y / 2; y < window.GetSize().y / 2; y += spriteSize.y)
		{
			mb::graphics::Sprite2D* sprite = new mb::graphics::Sprite2D({ x, y }, spriteSize);
			sprite->SetColor({0.2f, (float) rand() / RAND_MAX, 0.7f});
			sprites[index] = sprite;
			index++;
		}
	}

	mb::maths::Vec4 clearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	std::cout << "Drawing " << spriteCount << " sprites!" << std::endl;

	while (window.Open())
	{
		mb::utils::Update(window);
		window.Clear(clearColor);

		batch.Begin();

		for (unsigned int i = 0; i < spriteCount; i++)
		{
			//std::cout << i << std::endl;
			batch.Submit(sprites[i]);
		}

		batch.End();

		window.Update();
	}

	//free(sprites);
	
	for (unsigned int i = 0; i < spriteCount; i++)
	{
		delete sprites[i];
	}

	mb::utils::Terminate();

	//std::cin.get();

	return 0;
}