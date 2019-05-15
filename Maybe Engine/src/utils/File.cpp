#include "File.h"

namespace mb { namespace utils {

	InFile::InFile(const char* path)
		: m_Path(path), m_File(path, std::ifstream::binary), m_Read(false), m_CurrentLine(0)
	{
		if (!m_File.is_open())
			Log::Error("Error while trying to open file {}", path);
	}

	InFile::~InFile()
	{
		Close();
	}

	std::string InFile::Read()
	{
		std::stringstream ss;

		if (!m_Read)
		{
			std::string line;

			while (getline(m_File, line))
			{
				ss << line << '\n';
				m_Lines.push_back(line);
			}

			m_Read = true;

			return ss.str();
		}
		else
		{
			for (unsigned int i = 0; i < m_Lines.size(); i++)
			{
				ss << m_Lines[i] << '\n';
			}
		}

		return ss.str();
	}

	std::string InFile::NextLine()
	{
		if (m_CurrentLine > m_Lines.size() - 1)
			m_CurrentLine = 0;

		std::string line = m_Lines[m_CurrentLine];

		m_CurrentLine++;

		return line;
	}

	std::string InFile::GetLine(unsigned int line) const
	{
		if (line > 0 && line < m_Lines.size())
		{
			return m_Lines[line];
		}
		else
		{
			Log::Warn("Error: trying to get a non-existing line from file {}!", m_Path);
			return "";
		}
	}

	std::string InFile::GetLines(unsigned int start, unsigned int end) const
	{
		if (start > 0 && start < m_Lines.size() && end > 0 && end < m_Lines.size())
		{
			std::stringstream ss;
			
			for (unsigned int i = start; i < end; i++)
			{
				ss << m_Lines[i] << '\n';
			}

			return ss.str();
		}
		else
		{
			Log::Warn("Error: trying to get non-existing lines from file {}!", m_Path);
			return "";
		}
	}

	void InFile::Reset()
	{
		m_CurrentLine = 0;
	}

	void InFile::Close()
	{
		if (m_File.is_open())
			m_File.close();
	}
	
	/*
	
	END OF IN FILE, START OF OUT FILE
	
	*/

	OutFile::OutFile(const char* path)
		: m_Path(path), m_File(path, std::ofstream::app)
	{
		if (!m_File.is_open())
			Log::Error("Error while trying to open file {}", path);
	}

	OutFile::~OutFile()
	{
		Close();
	}

	void OutFile::Clear()
	{
		m_File.close();
		m_File.open(m_Path, std::ofstream::out | std::ofstream::trunc);
	}

	void OutFile::Close()
	{
		if (m_File.is_open())
			m_File.close();
	}

} }