#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <cstdarg>
#include <sstream>
#include <regex>

#include "rang.hpp"

#define DEBUG_LOG 0
#define ERROR_LOG 1

#define REGULAR_COLOR_MODE 0
#define BRIGHT_COLOR_MODE 1

namespace mb { namespace utils {

	struct TimeFormat
	{
		int hour, minute, second;
	};

	struct ConsoleColor
	{
		rang::bg bg = rang::bg::black;
		rang::fg fg;
		rang::fgB fgB;
		rang::bgB bgB;
		unsigned int fgMode = REGULAR_COLOR_MODE;
		unsigned int bgMode = REGULAR_COLOR_MODE;

		void SetForegroundColor(rang::fg color)
		{
			fgMode = REGULAR_COLOR_MODE;
			fg = color;
		}

		void SetBrightForegroundColor(rang::fgB color)
		{
			fgMode = BRIGHT_COLOR_MODE;
			fgB = color;
		}

		void SetBackgroundColor(rang::bg color)
		{
			bgMode = REGULAR_COLOR_MODE;
			bg = color;
		}

		void SetBrightBackgroundColor(rang::bgB color)
		{
			bgMode = BRIGHT_COLOR_MODE;
			bgB = color;
		}

		void SetOutputColors()
		{
			if (bgMode == REGULAR_COLOR_MODE)
				std::cout << bg;
			else if (bgMode == BRIGHT_COLOR_MODE)
				std::cout << bgB;

			if (fgMode == REGULAR_COLOR_MODE)
				std::cout << fg;
			else if (fgMode == BRIGHT_COLOR_MODE)
				std::cout << fgB;
		}
	};

	class Log
	{
	public:
		static void Init();
	
		static TimeFormat GetTime();

		template<typename ...Param>
		static void Debug(const char* message, const Param& ...params)
		{
#ifdef _DEBUG
			LogMessageWithTime(GetFullMessage(message, params...).c_str(), debugColors);
#endif
		}

		template<typename ...Param>
		static void Warn(const char* message, const Param& ...params)
		{
			LogMessageWithTime(GetFullMessage(message, params...).c_str(), warningColors);
		}

		template<typename ...Param>
		static void Error(const char* message, const Param& ...params)
		{
			LogMessageWithTime(GetFullMessage(message, params...).c_str(), errorColors);
		}

		static void SetColor(int mode, ConsoleColor color);
	private:
		template<typename First, typename ...Param>
		static std::string FillIn(std::vector<std::string> parts, std::string& str, const First& first)
		{
			//std::cout << first << std::endl;
			std::stringstream stream;
			str.append(parts[0]);
			stream << str << first;
			parts.erase(parts.begin());
			stream << parts[0];
			return stream.str();
		}

		template<typename First, typename ...Param>
		static std::string FillIn(std::vector<std::string> parts, std::string& str, const First& first, const Param& ...params)
		{
			str.append(parts[0]);
			str.append(std::to_string(first));
			parts.erase(parts.begin());

			return FillIn(parts, str, params...);
		}

		static std::vector<std::string> GetParts(const char* message)
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

			parts.push_back(str);

			return parts;
		}

		template<typename First, typename ...Param>
		static std::string GetFullMessage(const char* message, const First& first, const Param& ...params)
		{
			std::string str;
			std::vector<std::string> parts = GetParts(message);
			std::string fullMessage = FillIn(parts, str, first, params...);

			return fullMessage;
		}

		static std::string GetFullMessage(const char* message)
		{
			return std::string(message);
		}

		static void LogMessageWithTime(const char* message, ConsoleColor colors);
	private:
		static ConsoleColor reset;
		static ConsoleColor debugColors;
		static ConsoleColor warningColors;
		static ConsoleColor errorColors;
	};

} }