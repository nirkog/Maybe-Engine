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

		const char* zeros[3];
		if (time.hour < 10) zeros[0] = "0"; else zeros[0] = "";
		if (time.minute < 10) zeros[1] = "0"; else zeros[1] = "";
		if (time.second < 10) zeros[2] = "0"; else zeros[2] = "";

		std::cout << colors.bg << colors.fg;
		std::cout << "[" << 
			zeros[0] << time.hour << ":" <<
			zeros[1] << time.minute << ":" <<
			zeros[2] << time.second << "] " <<
			message << std::endl;
		std::cout << reset.bg << reset.fg;
	}

} }