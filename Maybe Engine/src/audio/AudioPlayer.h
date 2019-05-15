#pragma once

#include "AlSource.h"
#include "Sound.h"

namespace mb { namespace audio {

	class AudioPlayer
	{
	public:
		AudioPlayer();
		~AudioPlayer();

		void Play(Sound& sound);

		void Setf(ALenum param, float val) { alSourcef(m_Source.GetID(), param, val); };
		void Set3f(ALenum param, float val1, float val2, float val3) { alSource3f(m_Source.GetID(), param, val1, val2, val3); };
	private:
		AlSource m_Source;
	};

} }