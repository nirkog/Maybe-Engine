#include "Sound.h"

namespace mb { namespace audio {

	Sound::Sound(const char* path)
		: m_Path(path)
	{

	}

	Sound::~Sound()
	{

	}

	void Sound::Load()
	{
		if (WavFile::IsWav(m_Path))
		{
			WavFile file(m_Path);
			file.Read();
			m_Buffer.SetData(file.GetData(), file.GetMetaData());
		}
		else
		{
			utils::Log::Warn("File type of file '{}' is not supported", m_Path);
		}
	}

} }