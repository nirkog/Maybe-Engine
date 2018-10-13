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

#define WIDTH 1200
#define HEIGHT 800

bool intersects(mb::graphics::Sprite2D& first, mb::graphics::Sprite2D& second);

int main()
{
	srand((unsigned int) time(NULL));
	mb::utils::Init();

	mb::graphics::Window window(WIDTH, HEIGHT, "Maybe This Will Work");
	window.QuitOnPress(GLFW_KEY_ESCAPE);
	mb::utils::Time::EnableFpsLog();
	std::cout << glGetString(GL_RENDERER) << std::endl;

	mb::maths::Vec4 clearColor(0.1f, 0.1f, 0.1f, 1.0f);

	mb::graphics::BatchRenderer renderer(window);

	//mb::maths::Vec2 spriteSize = {50.0f, 50.0f};
	//unsigned int spriteCount = 0;

	//for (float x = -window.GetSize().x / 2 + spriteSize.x / 2; x < window.GetSize().x / 2; x += spriteSize.x)
	//{
	//	for (float y = -window.GetSize().y / 2 + spriteSize.y / 2; y < window.GetSize().y / 2; y += spriteSize.y)
	//	{
	//		spriteCount++;
	//	}
	//}

	//mb::graphics::Sprite2D** sprites = (mb::graphics::Sprite2D**) malloc(sizeof(mb::graphics::Sprite2D) * spriteCount);
	//unsigned int index = 0;

	//for (float x = -window.GetSize().x / 2 + spriteSize.x / 2; x < window.GetSize().x / 2; x += spriteSize.x)
	//{
	//	for (float y = -window.GetSize().y / 2 + spriteSize.y / 2; y < window.GetSize().y / 2; y += spriteSize.y)
	//	{
	//		mb::graphics::Sprite2D* sprite = new mb::graphics::Sprite2D({ x, y }, spriteSize);
	//		//sprite->SetColor({0.9f, (float) rand() / RAND_MAX, 0.9f});
	//		sprite->SetTexture(index % 2 == 0 ? "./res/smiley.png" : "./res/sadface.png");
	//		sprites[index] = sprite;
	//		index++;
	//	}
	//}

	//std::cout << "Drawing " << spriteCount << " sprites!" << std::endl;

	const float speed = 200;
	mb::graphics::Sprite2D spaceship({ 0, -HEIGHT / 2 + 40 }, { 100, 100 });
	spaceship.SetTexture("./res/spaceship.png");

	const float bulletSpeed = 350;
	std::vector<mb::graphics::Sprite2D> bullets;

	std::vector<mb::graphics::Sprite2D*> aliens;
	std::vector<mb::graphics::Sprite2D*> alienBullets;
	const mb::maths::Vec2 alienSize = {60, 60};
	const unsigned int rows = 2, columns = 10;
	const float start = 100;
	const mb::maths::Vec2 padding((WIDTH - (2 * start - (alienSize.x / 2)) - columns * alienSize.x) / columns, 15);
	float alienShootingRate = 1.75f;
	mb::utils::Timer alienShootingTimer;

	for (unsigned int x = 0; x < columns; x++)
	{
		for (unsigned int y = 0; y < rows; y++)
		{
			mb::graphics::Sprite2D *alien = new mb::graphics::Sprite2D(
				{ (float) x * (alienSize.x + padding.x) - WIDTH / 2 + (start + alienSize.x / 2), (float) y * (alienSize.y + padding.y) + HEIGHT / 4 },
				alienSize
			);
			alien->SetTexture("./res/alien.png");
			aliens.push_back(alien);
		}
	}

	while (window.Open())
	{
		mb::utils::Update(window);
		window.Clear(clearColor);

		renderer.Begin();

		//INPUT

		if (mb::input::Input::IsKeyDown(mb::input::Key::SPACE))
		{
			mb::graphics::Sprite2D bullet(spaceship.transform.position, {5, 15});
			bullet.SetColor({0.7f, 0.25f, 0.1f});
			bullets.push_back(bullet);
		}

		if (mb::input::Input::IsKeyPressed(mb::input::Key::D))
			spaceship.transform.position.x += speed * mb::utils::Time::GetDeltaTime();
		else if (mb::input::Input::IsKeyPressed(mb::input::Key::A))
			spaceship.transform.position.x -= speed * mb::utils::Time::GetDeltaTime();

		//UPDATE

		if (alienShootingTimer.Time() >= alienShootingRate)
		{
			mb::graphics::Sprite2D* parent = aliens[(float) rand() / RAND_MAX * (aliens.size() - 1)];
			mb::graphics::Sprite2D* bullet = new mb::graphics::Sprite2D(parent->transform.position, { 5, 15 });
			bullet->SetTexture("./res/alien.png");
			alienBullets.push_back(bullet);
			alienShootingTimer.Clear();
		}

		if (spaceship.transform.position.x + 40 > WIDTH / 2)
			spaceship.transform.position.x = WIDTH / 2 - 40;
		else if (spaceship.transform.position.x - 40 < -WIDTH / 2)
			spaceship.transform.position.x = -WIDTH / 2 + 40;

		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			bool hit = false;
			bullets[i].transform.position.y += bulletSpeed * mb::utils::Time::GetDeltaTime();

			for (unsigned int j = 0; j < aliens.size(); j++)
			{
				if (intersects(bullets[i], *aliens[j]))
				{
					alienShootingRate -= 0.05f;

					if (alienShootingRate < 0.1f) alienShootingRate = 0.1f;

					delete aliens[j];
					aliens.erase(aliens.begin() + j);
					bullets.erase(bullets.begin() + i);
					i--;
					hit = true;

					if (aliens.size() == 0)
						window.Close();

					break;
				}
			}

			if (hit) continue;
		
			if (bullets[i].transform.position.y + 5 > HEIGHT / 2)
			{
				bullets.erase(bullets.begin() + i);
				i--;
			}
		}

		for (unsigned int i = 0; i < alienBullets.size(); i++)
		{
			alienBullets[i]->transform.position.y -= bulletSpeed * mb::utils::Time::GetDeltaTime();

			if (intersects(*alienBullets[i], spaceship))
			{
				for (unsigned int j = 0; j < aliens.size(); j++)
					delete aliens[j];
				aliens.clear();

				for (unsigned int x = 0; x < columns; x++)
				{
					for (unsigned int y = 0; y < rows; y++)
					{
						mb::graphics::Sprite2D *alien = new mb::graphics::Sprite2D(
							{ (float)x * (alienSize.x + padding.x) - WIDTH / 2 + (start + alienSize.x / 2), (float)y * (alienSize.y + padding.y) + HEIGHT / 4 },
							alienSize
						);
						alien->SetTexture("./res/alien.png");
						aliens.push_back(alien);
					}
				}

				bullets.clear();
				alienBullets.clear();

				alienShootingRate = 1.75f;

				spaceship.transform.position = { 0, -HEIGHT / 2 + 40 };
				break;
			}
		}

		//RENDER

		for (unsigned int i = 0; i < alienBullets.size(); i++)
			renderer.Submit(alienBullets[i]);

		for (unsigned int i = 0; i < bullets.size(); i++)
			renderer.Submit(&bullets[i]);

		for (unsigned int i = 0; i < aliens.size(); i++)
			renderer.Submit(aliens[i]);

		renderer.Submit(&spaceship);

		renderer.End();

		window.Update();
	}

	//free(sprites);
	
	/*for (unsigned int i = 0; i < spriteCount; i++)
	{
		delete sprites[i];
	}*/

	for (unsigned int i = 0; i < aliens.size(); i++)
	{
		delete aliens[i];
	}

	mb::utils::Terminate();

	//std::cin.get();

	return 0;
}

bool intersects(mb::graphics::Sprite2D& first, mb::graphics::Sprite2D& second)
{
	if (first.transform.position.x + first.GetSize().x / 2 >= second.transform.position.x - second.GetSize().x / 2
		&& first.transform.position.x - first.GetSize().x / 2 <= second.transform.position.x + second.GetSize().x / 2)
	{
		if (first.transform.position.y - first.GetSize().y / 2 <= second.transform.position.y + second.GetSize().y / 2
			&& first.transform.position.y + first.GetSize().y / 2 >= second.transform.position.y - second.GetSize().y / 2)
		{
			return true;
		}
	}

	return false;
}