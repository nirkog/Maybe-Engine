#include "Time.h"

#include <iostream>
#include "Log.h"

namespace mb { namespace utils {

	std::vector<Timer*> Time::timers;
	float Time::deltaTime = 0, Time::oldTime = 0, Time::fpsTimer = 0;
	unsigned int Time::currentFPS = 0, Time::frames = 0;
	bool Time::logFPS = false;

	void Time::Update()
	{
		deltaTime = (float) glfwGetTime() - oldTime;
		oldTime = (float) glfwGetTime();

		for (unsigned int i = 0; i < timers.size(); i++)
		{
			timers[i]->Update(deltaTime);
		}

		fpsTimer += deltaTime;
		frames++;

		if (fpsTimer >= 1.0f)
		{
			if (logFPS) Log::Debug("FPS: {}", frames);
			currentFPS = frames;
			fpsTimer = 0;
			frames = 0;
		}
	}

	unsigned int Time::AddTimer(Timer* timer)
	{
		unsigned int id = timers.size();
		timers.push_back(timer);

		return id;
	}

	void Time::RemoveTimer(Timer* timer)
	{
		timers.erase(timers.begin() + timer->GetID());
	}

	unsigned int AddToList(Timer* timer)
	{
		return Time::AddTimer(timer);
	}

	void RemoveFromList(Timer* timer)
	{
		Time::RemoveTimer(timer);
	}

} }