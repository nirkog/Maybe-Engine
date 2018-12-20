#include "Log.h"

#include <string>

namespace mb { namespace utils {

	ConsoleColor Log::reset;
	ConsoleColor Log::debugColors;
	ConsoleColor Log::errorColors;

	void Log::Init()
	{
		reset = { rang::bg::reset, rang::fg::reset };
		debugColors = { rang::bg::black, rang::fg::green };
		errorColors = { rang::bg::gray, rang::fg::red};
	}

	TimeFormat Log::GetTime()
	{
		std::time_t t = std::time(NULL);
		std::tm* now = std::localtime(&t);

		return { now->tm_hour, now->tm_min, now->tm_sec };
	}

	void Log::SetColor(int mode, ConsoleColor color)
	{
		switch(mode)
		{ 
		case DEBUG_LOG:
			debugColors = color;
			break;
		case ERROR_LOG:
			errorColors = color;
			break;
		}
	}
	
	void Log::LogMessageWithTime(const char* message, ConsoleColor colors)
	{
		TimeFormat time = GetTime();

		std::cout << colors.bg << colors.fg;
		std::cout << "[" << time.hour << ":" << time.minute << ":" << time.second << "] " << message << std::endl;
		std::cout << reset.bg << reset.fg;
	}

	void Log::Debug(const char* message)
	{
	#ifdef _DEBUG
		LogMessageWithTime(message, debugColors);
	#endif
	}

	void Log::Error(const char* message)
	{
		std::cout << rang::style::bold;
		LogMessageWithTime(message, errorColors);
	}

} }