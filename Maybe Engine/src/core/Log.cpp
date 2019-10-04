#include "Log.h"

#include <string>

namespace mb {

	Log::ConsoleColor Log::reset = { rang::bg::reset, rang::fg::reset };
	Log::ConsoleColor Log::debugColors = { rang::bg::black, rang::fg::green };
	Log::ConsoleColor Log::warningColors = { rang::bg::black, rang::fg::gray, rang::fgB::yellow, rang::bgB::black, BRIGHT_COLOR_MODE };
	Log::ConsoleColor Log::errorColors = { rang::bg::gray, rang::fg::red };

	Log::TimeFormat Log::GetTime()
	{
		std::time_t t = std::time(NULL);
		std::tm* now = std::localtime(&t);

		return { now->tm_hour, now->tm_min, now->tm_sec };
	}

	void Log::SetColor(int mode, Log::ConsoleColor color)
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
	
	void Log::LogMessageWithTime(const char* message, Log::ConsoleColor colors)
	{
		TimeFormat time = GetTime();

		const char* zeros[3];
		if (time.hour < 10) zeros[0] = "0"; else zeros[0] = "";
		if (time.minute < 10) zeros[1] = "0"; else zeros[1] = "";
		if (time.second < 10) zeros[2] = "0"; else zeros[2] = "";

		colors.SetOutputColors();
		std::cout << "[" << 
			zeros[0] << time.hour << ":" <<
			zeros[1] << time.minute << ":" <<
			zeros[2] << time.second << "] " <<
			message << std::endl;
		std::cout << reset.bg << reset.fg;
	}

} 