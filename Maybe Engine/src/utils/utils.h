#pragma once

#include "Timer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace mb { namespace utils {

	bool logFPS = false;
	float oldTime = 0;
	float deltaTime = 0;
	float fpsTimer = 0;
	float fps = 0;
	unsigned int frames = 0;
	std::vector<mb::utils::Timer*> timers;

	void Init()
	{
		glfwInit();
	}

	void Terminate()
	{
		glfwTerminate();
	}

	void EnableFpsLog()
	{
		if (!logFPS) logFPS = true;
	}

	void DisableFpsLog()
	{
		if (logFPS) logFPS = false;
	}

	void Update()
	{
		deltaTime = (float)glfwGetTime() - oldTime;
		oldTime = (float)glfwGetTime();
		frames++;

		fpsTimer += deltaTime;

		for (unsigned int i = 0; i < timers.size(); i++)
		{
			timers[i]->Update(deltaTime);
		}

		if (fpsTimer >= 1.0f)
		{
			if (logFPS) std::cout << "fps: " << frames << std::endl;
			fps = frames;
			fpsTimer = 0;
			frames = 0;
		}
	}

	unsigned int AddToList(Timer* timer)
	{
		unsigned int id = timers.size();
		timers.push_back(timer);

		return id;
	}

	void RemoveFromList(Timer* timer)
	{
		//std::cout << "Removed timer with ID " << timer->GetID() << "!" << std::endl;
		timers.erase(timers.begin() + timer->GetID());
	}

} }