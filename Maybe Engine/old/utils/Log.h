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

#define PREFIX_LENGTH 11

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
#if _DEBUG
			if (GetParts(message).size() == 1 && sizeof...(params) > 0)
			{
				char* str = GetPlaceholderString(message, params...);

				LogMessageWithTime(GetFullMessage(str, message, params...).c_str(), debugColors);

				delete str;
			}
			else
			{
				LogMessageWithTime(GetFullMessage(message, params...).c_str(), debugColors);
			}
#endif
		}

		template<typename T>
		static void Debug(const std::vector<T> vec)
		{
#if _DEBUG
			std::stringstream stream;

			stream << "[";
			for (unsigned int i = 0; i < vec.size(); i++)
			{
				if (i < vec.size() - 1)
					stream << vec[i] << ", ";
				else
					stream << vec[i] << "]";
			}

			LogMessageWithTime(stream.str().c_str(), debugColors);
#endif
		}

		template<typename ...Param>
		static void Debug(const Param& ...params)
		{
#if _DEBUG
			char* str = GetPlaceholderString(params...);

			LogMessageWithTime(GetFullMessage(str, params...).c_str(), debugColors);

			delete str;
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
		template<typename Param>
		static std::string WrapNewLines(const Param& param)
		{
			std::stringstream testStream;
			testStream << param;

			std::string str = testStream.str();
			std::stringstream temp;
			std::vector<std::string> strParts;
			std::stringstream result;

			char spaces[PREFIX_LENGTH + 1];
			spaces[PREFIX_LENGTH] = '\0';

			for (unsigned int i = 0; i < PREFIX_LENGTH; i++) spaces[i] = ' ';

			for (unsigned int i = 0; i < str.size(); i++)
			{
				if (str[i] == '\n')
				{
					strParts.push_back(temp.str());
					temp.str(std::string());
				}
				else
				{
					temp << str[i];
				}
			}

			for (unsigned i = 0; i < strParts.size(); i++)
			{
				if (i < strParts.size() - 1)
					result << strParts[i] << std::endl << spaces;
				else
					result << strParts[i] << std::endl;
			}

			if (strParts.size() == 0) return str;
			else return result.str();
		}

		template<typename ...Param>
		static char* GetPlaceholderString(const Param& ...params)
		{
			const unsigned int count = (const unsigned int) sizeof...(params);
			const unsigned int strSize = count * 2 + (count - 1);
			char* str = (char*)malloc(strSize + 1);
			str[strSize] = '\0';
			unsigned int offset = 0;

			for (unsigned int i = 0; i < count; i++)
			{
				str[offset] = '{';
				str[offset + 1] = '}';

				if (i < count - 1)
				{
					str[offset + 2] = ' ';

					offset += 3;
				}
			}

			return str;
		}

		template<typename First, typename ...Param>
		static std::string FillIn(std::vector<std::string> parts, std::string& str, const First& first)
		{
			std::stringstream stream;
			str.append(parts[0]);
			stream << str << WrapNewLines(first);
			parts.erase(parts.begin());
			stream << parts[0];
			return stream.str();
		}

		template<typename First, typename ...Param>
		static std::string FillIn(std::vector<std::string> parts, std::string& str, const First& first, const Param& ...params)
		{
			std::stringstream stream;
			stream << str << parts[0] << WrapNewLines(first);
			str = stream.str();
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