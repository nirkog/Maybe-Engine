#include "File.h"

#include <iostream>

namespace mb {

	SeekDir File::Beg = SeekDir::Beg;
	SeekDir File::Cur = SeekDir::Cur;
	SeekDir File::End = SeekDir::End;

	File::File(const char* path)
		: m_Length(0), m_Position(0), m_Worker(nullptr), m_Open(true)
	{
		/*
		
		CHECK FOR ERRORS!
		
		*/

		m_Stream.open(path, std::fstream::in | std::fstream::out | std::fstream::binary);

		UpdateLength();
	}

	File::~File()
	{
		Close();

		if (m_Worker)
		{
			m_Worker->join();
			delete m_Worker;
		}
	}

	void File::Read(char* buffer, unsigned int length)
	{
		m_Stream.read(buffer, length);

		m_Position += length;
	}

	char* File::Read(unsigned int length, FileType type)
	{
		unsigned int bufferLength = sizeof(char) * length + sizeof(char) * (((int) type) ^ 1);
		char* buffer = (char*) malloc(bufferLength);
		if (type == FileType::String) buffer[length] = '\0';

		m_Stream.read(buffer, length);

		m_Position += length;

		return buffer;
	}

	void File::GetLine(char* buffer)
	{
		m_Stream.getline(buffer, m_Length - m_Position);
		m_Position = (unsigned int) m_Stream.tellg();
	}

	void File::GetChar(char& buffer)
	{
		m_Stream.get(buffer);
		m_Position++;
	}

	void File::AsyncRead(char* buffer, unsigned int length, void (*callback)())
	{
		m_Worker = new std::thread([this, buffer, length, callback] {
			this->Read(buffer, length);

			if (callback != nullptr) callback();
		});
	}

	void File::AsyncWait()
	{
		m_Worker->join();
	}

	void File::Write(const char* string, unsigned int length)
	{
		m_Stream.write(string, length);

		UpdateLength();

		m_Position += length;
	}

	void File::Flush()
	{
		m_Stream.flush();

		UpdateLength();

		m_Position = (unsigned int) m_Stream.tellg();
	}

	void File::PutChar(char c)
	{
		m_Stream.put(c);

		UpdateLength();

		m_Position++;
	}

	void File::Close()
	{
		m_Stream.close();

		m_Open = false;
	}

	void File::SeekRead(unsigned int position)
	{
		m_Stream.seekg(position);

		m_Position = position;
	}

	void File::SeekRead(unsigned int offset, SeekDir dir)
	{
		m_Stream.seekg(offset, (int) dir);

		if (dir == SeekDir::Beg) m_Position = offset;
		else if (dir == SeekDir::Cur) m_Position += offset;
		else if (dir == SeekDir::End) m_Position = m_Length + offset;
	}

	void File::SeekWrite(unsigned int position)
	{
		m_Stream.seekp(position);

		m_Position = position;
	}

	void File::SeekWrite(unsigned int offset, SeekDir dir)
	{
		m_Stream.seekp(offset, (int) dir);

		if (dir == SeekDir::Beg) m_Position = offset;
		else if (dir == SeekDir::Cur) m_Position += offset;
		else if (dir == SeekDir::End) m_Position = m_Length + offset;
	}

	void File::UpdateLength()
	{
		m_Stream.seekg(0, m_Stream.end);
		m_Length = (unsigned int) m_Stream.tellg();
		m_Stream.seekg(0, m_Stream.beg);
	}

	File::FileError File::GetError() const
	{
		return { m_Stream.bad(), m_Stream.fail(), m_Stream.eof() };
	}

}