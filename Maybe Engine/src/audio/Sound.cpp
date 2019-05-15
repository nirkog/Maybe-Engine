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
		WavFile file(m_Path);
		file.Read();
		m_Buffer.SetData(file.GetData(), file.GetMetaData());
	}

} }