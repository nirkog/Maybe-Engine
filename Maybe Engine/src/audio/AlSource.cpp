#include "AlSource.h"

namespace mb { namespace audio {

	AlSource::AlSource()
	{
		ALCall(alGenSources(1, &m_ID));
		ALCall(alSourcef(m_ID, AL_GAIN, 1));
		ALCall(alSourcef(m_ID, AL_PITCH, 1));
		ALCall(alSource3f(m_ID, AL_POSITION, 0, 0, 0));
	}

	AlSource::~AlSource()
	{
		ALCall(alDeleteSources(1, &m_ID));
	}

	void AlSource::Play(unsigned int buffer) const
	{
		ALCall(alSourcei(m_ID, AL_BUFFER, buffer));
		ALCall(alSourcePlay(m_ID));
	}

} }