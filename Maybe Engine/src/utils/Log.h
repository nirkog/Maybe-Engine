#pragma once

#include <iostream>
#include <ctime>
#include <cstdarg>
#include <regex>

#include "rang.hpp"

#define DEBUG_LOG 0
#define ERROR_LOG 1

namespace mb { namespace utils {

	struct TimeFormat
	{
		int hour, minute, second;
	};

	struct ConsoleColor
	{
		rang::bg bg;
		rang::fg fg;
	};

	class Log
	{
	public:
		static void Init();
	
		static TimeFormat GetTime();

		static void Debug(const char* message);
		static void Error(const char* message);

		template<typename ...Param>
		static void Test(const char* message, const Param& ...params)
		{
			std::string str(message);
			std::regex regex("(\\{\\})");
			std::smatch matches;

			std::vector<std::string> parts;

			while (std::regex_search(str, matches, regex))
			{
				parts.push_back(str.substr(0, matches.position()));
				str = matches.suffix().str();
			}
		}

		static void SetColor(int mode, ConsoleColor color);
	private:
		static void LogMessageWithTime(const char* message, ConsoleColor colors);
	private:
		static ConsoleColor reset;
		static ConsoleColor debugColors;
		static ConsoleColor errorColors;
	};

} }