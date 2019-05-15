#pragma once

#include <vector>
#include <fstream>

#include "MetaData.h"
#include "..\utils\Log.h"

namespace mb { namespace audio {

	struct WavMeta
	{
		char chunkID[5];
		int chunkSize;
		char format[5];
		char subChunk1ID[5];
		int subChunk1Size;
		short audioFormat;
		short numChannels;
		int sampleRate;
		int byteRate;
		short blockAlign;
		short bitsPerSample;
		char subChunk2ID[5];
		int subChunk2Size;
	};

	class WavFile
	{
	public:
		WavFile(const char* path);
		~WavFile();

		char* Read();
		char* GetData() { return m_Data; };

		const unsigned int GetLength() const { return m_Length; }

		const MetaData GetMetaData() const { return m_Meta; }
		void PrintMetaData() const;

		void Close();
	private:
		const char* m_Path;
		std::ifstream m_File;
		char* m_Data;
		bool m_Read;
		unsigned int m_Length;
		WavMeta m_WavMeta;
		MetaData m_Meta;
	};

} }

