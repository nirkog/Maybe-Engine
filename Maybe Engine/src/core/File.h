#pragma once

#include <chrono>
#include <thread>
#include <fstream>

namespace mb {

	enum class FileType
	{
		String=0, Binary=1
	};

	enum class SeekDir
	{
		Beg=std::ios_base::beg, Cur=std::ios_base::cur, End=std::ios_base::end
	};

	class File 
	{
	struct FileError
	{
		bool Bad, Fail, Eof;
	};
	public:
		File(const char* path);
		~File();

		const unsigned int Length() inline const { return m_Length; };

		void Read(char* buffer, unsigned int length);
		char* Read(unsigned int length, FileType type=FileType::String);
		void GetLine(char* buffer);
		void GetChar(char& buffer);

		void AsyncRead(char* buffer, unsigned int length, void (*callback)()=nullptr);
		void AsyncWait();

		void Write(const char* string, unsigned int length);
		void PutChar(char c);
		void Flush();

		void Close();
		
		bool IsOpen() inline const { return m_Open; }

		void SeekRead(unsigned int position);
		void SeekRead(unsigned int offset, SeekDir dir);

		void SeekWrite(unsigned int position);
		void SeekWrite(unsigned int offset, SeekDir dir);

		unsigned int Tell() inline const { return m_Position; }

		FileError GetError() const;
	private:
		void UpdateLength();
	public:
		static SeekDir Beg;
		static SeekDir Cur;
		static SeekDir End;
	private:
		std::fstream m_Stream;
		unsigned int m_Length;
		unsigned int m_Position;
		const char* m_Path;
		std::thread* m_Worker;
		bool m_Open;
	};

}