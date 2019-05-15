#include "WavFile.h"

namespace mb { namespace audio {

	WavFile::WavFile(const char* path)
		: m_File(path, std::ifstream::binary), m_Read(false), m_Length(0), m_Path(path), m_Data(nullptr)
	{
		if (!m_File.is_open())
		{
			utils::Log::Error("Error while trying to open file {}", path);
		}
		else
		{
			m_File.seekg(0, m_File.end);
			m_Length = m_File.tellg();
			m_File.seekg(0, m_File.beg);
		}

	}


	WavFile::~WavFile()
	{
		if (m_Data != nullptr) delete m_Data;

		Close();
	}

	char* WavFile::Read()
	{
		if (!m_Read)
		{
			char* buffer = (char*)malloc(4);

			m_File.seekg(0, m_File.beg);

			m_File.read(m_WavMeta.chunkID, 4);
			m_WavMeta.chunkID[4] = 0;
			
			m_File.read(buffer, 4);
			memcpy(&m_WavMeta.chunkSize, buffer, 4);

			m_File.read(m_WavMeta.format, 4);
			m_WavMeta.format[4] = 0;

			m_File.read(m_WavMeta.subChunk1ID, 4);
			m_WavMeta.subChunk1ID[4] = 0;

			m_File.read(buffer, 4);
			memcpy(&m_WavMeta.subChunk1Size, buffer, 4);

			m_File.read(buffer, 2);
			memcpy(&m_WavMeta.audioFormat, buffer, 2);

			m_File.read(buffer, 2);
			memcpy(&m_WavMeta.numChannels, buffer, 2);

			m_File.read(buffer, 4);
			memcpy(&m_WavMeta.sampleRate, buffer, 4);

			m_File.read(buffer, 4);
			memcpy(&m_WavMeta.byteRate, buffer, 4);

			m_File.read(buffer, 2);
			memcpy(&m_WavMeta.blockAlign, buffer, 2);

			m_File.read(buffer, 2);
			memcpy(&m_WavMeta.bitsPerSample, buffer, 2);

			m_File.read(m_WavMeta.subChunk2ID, 4);
			m_WavMeta.subChunk2ID[4] = 0;

			m_File.read(buffer, 4);
			memcpy(&m_WavMeta.subChunk2Size, buffer, 4);

			m_Data = (char*)malloc(m_WavMeta.subChunk2Size);
			m_File.read(m_Data, m_WavMeta.subChunk2Size);

			m_Meta.format = m_WavMeta.format;
			m_Meta.dataSize = m_WavMeta.subChunk2Size;
			m_Meta.sampleRate = m_WavMeta.sampleRate;
			m_Meta.numChannels = m_WavMeta.numChannels;
			m_Meta.bitsPerSample = m_WavMeta.bitsPerSample;

			delete buffer;
		}

		return m_Data;
	}

	void WavFile::PrintMetaData() const
	{
		utils::Log::Debug("Chunk ID: {}", m_WavMeta.chunkID);
		utils::Log::Debug("Chunk size: {}", m_WavMeta.chunkSize);
		utils::Log::Debug("Format: {}", m_WavMeta.format);
		utils::Log::Debug("SubChunk1ID: {}", m_WavMeta.subChunk1ID);
		utils::Log::Debug("SubChunk1Size: {}", m_WavMeta.subChunk1Size);
		utils::Log::Debug("Audio format: {}", m_WavMeta.audioFormat);
		utils::Log::Debug("Num Channels: {}", m_WavMeta.numChannels);
		utils::Log::Debug("Sample rate: {}", m_WavMeta.sampleRate);
		utils::Log::Debug("Byte rate: {}", m_WavMeta.byteRate);
		utils::Log::Debug("Block align: {}", m_WavMeta.blockAlign);
		utils::Log::Debug("Bits per sample: {}", m_WavMeta.bitsPerSample);
		utils::Log::Debug("SubChunk2ID: {}", m_WavMeta.subChunk2ID);
		utils::Log::Debug("SubChunk2Size: {}", m_WavMeta.subChunk2Size);
	}

	void WavFile::Close()
	{
		if (m_Read)
			m_File.close();
	}

} }