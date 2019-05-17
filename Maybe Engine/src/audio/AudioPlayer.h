#pragma once

#include "AlSource.h"
#include "Sound.h"

#include "..\maths\vec3.h"

namespace mb { namespace audio {

	class AudioPlayer
	{
	public:
		AudioPlayer();
		~AudioPlayer();

		void Play(Sound& sound);

		void SetPosition(const maths::Vec3& position) { Set3f(AL_POSITION, position.x, position.y, position.z); }
		void SetPosition(float x, float y, float z) { Set3f(AL_POSITION, x, y, z); }
		void SetVelocity(const maths::Vec3& velocity) { Set3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z); }
		void SetVelocity(float x, float y, float z) { Set3f(AL_VELOCITY, x, y, z); }
		void SetDirection(const maths::Vec3& direction) { Set3f(AL_DIRECTION, direction.x, direction.y, direction.z); }
		void SetDirection(float x, float y, float z) { Set3f(AL_DIRECTION, x, y, z); }

		void SetPitch(float pitch) { Setf(AL_PITCH, pitch); }
		void SetVolume(float volume) { Setf(AL_GAIN, volume); }
		void SetMinVolume(float min) { Setf(AL_MIN_GAIN, min);  }
		void SetMaxVolume(float max) { Setf(AL_MIN_GAIN, max);  }

		void SetLooping(bool looping) { Seti(AL_LOOPING, (int) looping); }
	private:
		void Setf(ALenum param, float val) { alSourcef(m_Source.GetID(), param, val); };
		void Set3f(ALenum param, float val1, float val2, float val3) { alSource3f(m_Source.GetID(), param, val1, val2, val3); };
		void Seti(ALenum param, int val) { alSourcei(m_Source.GetID(), param, val); }
	private:
		AlSource m_Source;
	};

} }