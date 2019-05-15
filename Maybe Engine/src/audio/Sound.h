#pragma once

#include "WavFile.h"
#include "AlBuffer.h"

namespace mb { namespace audio {

	class Sound
	{
	public:
		Sound(const char* path);
		~Sound();

		void Load();

		unsigned int GetBufferID() { return m_Buffer.GetID(); };
	private:
		const char* m_Path;
		AlBuffer m_Buffer;
	};

}}