#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Log.h"

namespace mb { namespace utils {

	class InFile
	{
	public:
		InFile(const char* path);
		~InFile();

		std::string Read();
		std::string NextLine();

		std::string GetLine(unsigned int line) const;
		std::string GetLines(unsigned int start, unsigned int end) const;

		void Reset();
		void Close();
	private:
		const char* m_Path;
		std::ifstream m_File;
		std::vector<std::string> m_Lines;
		bool m_Read;
		unsigned int m_CurrentLine;
	};

	class OutFile
	{
	public:
		OutFile(const char* path);
		~OutFile();

		void Clear();
		void Close();
		std::ofstream& GetBuffer() { return m_File; }
	private:
		const char* m_Path;
		std::ofstream m_File;
	};

} }