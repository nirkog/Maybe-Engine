#include "AudioPlayer.h"

namespace mb { namespace audio {

	AudioPlayer::AudioPlayer()
	{
	}

	AudioPlayer::~AudioPlayer()
	{

	}

	void AudioPlayer::Play(Sound& sound)
	{
		m_Source.Play(sound.GetBufferID());
	}

} }