#pragma once

#include <vector>

#include "../graphics/GL.h"
#include "Timer.h"

namespace mb { namespace utils {

	class Time
	{
	public:
		static void Update();

		inline static float GetDeltaTime() { return deltaTime; }
		inline static unsigned int GetFps() { return currentFPS; }
		inline static float GetElapsedTime() { return elapsedTime; }

		static unsigned int AddTimer(Timer* timer);
		static void RemoveTimer(Timer* timer);

		inline static void EnableFpsLog() { if(!logFPS) logFPS = true; };
		inline static void DisableFpsLog() { if(logFPS) logFPS = false; };
	private:
		static std::vector<mb::utils::Timer*> timers;
		static float deltaTime, oldTime, fpsTimer;
		static float elapsedTime;
		static unsigned int frames, currentFPS;
		static bool logFPS;
	};

} }