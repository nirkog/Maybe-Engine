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

void i(float interval)
{
	float r = (float) rand() / RAND_MAX;
	float g = (float) rand() / RAND_MAX;
	float b = (float) rand() / RAND_MAX;

	clearColor = {r, g, b};
	std::cout << clearColor << std::endl;

	//std::cout << "I am called every " << interval << " seconds." << std::endl;
}

int main()
{
	srand(time(NULL));
	mb::utils::Init();

	mb::graphics::Window window(800, 600, "Maybe This Will Work");
	glfwSwapInterval(0);

	window.QuitOnPress(GLFW_KEY_ESCAPE);

	mb::utils::DisableFpsLog();

	float vertices[] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	mb::graphics::BufferLayout layout;
	layout.Push<float>(2);
	layout.Push<unsigned char>(3);

	mb::graphics::Buffer VBO(vertices, 3 * 2 * sizeof(float));
	VBO.SetLayout(layout);

	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO.GetID());
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	mb::graphics::Shader shader("./res/basic.vert", "./res/basic.frag");

	mb::maths::Vec3 color(0, 0.2f, 0.8f);

	mb::utils::Timer timer;
	timer.SetFunctionAtInterval(i, 2);

	while (window.Open())
	{
		mb::utils::Update(window);
		window.Clear(clearColor.x, clearColor.y, clearColor.z, 1.0f);

		if (timer.GetIntervalCount() == 3)
		{
			window.SetTitle("Done for today!");
			timer.DisableInterval();
			timer.ClearIntervalCount();
		}

		if (mb::input::IsKeyReleased(mb::input::Key::J))
			i(1);

		color.z = abs(sin((float) glfwGetTime())) / 2.5;

		shader.Bind();
		shader.SetUniformVec3("u_Color", color);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.Update();
	}

	mb::utils::Terminate();

	//std::cin.get();

	return 0;
}