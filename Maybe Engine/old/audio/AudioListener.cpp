#include "AudioListener.h"

namespace mb { namespace audio {
		
	maths::Vec3 AudioListener::m_Position(0, 0, 0);
	maths::Vec3 AudioListener::m_Velocity(0, 0, 0);

	void AudioListener::SetPosition(const maths::Vec3& pos)
	{
		m_Position = pos;

		ALCall(alListener3f(AL_POSITION, pos.x, pos.y, pos.z));
	}

	void AudioListener::SetVelocity(const maths::Vec3& velocity)
	{
		m_Velocity = velocity;

		ALCall(alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z));
	}

} }