#pragma once

#include "..\maths\maths.h"

#include "AL.h"

namespace mb { namespace audio {

	class AudioListener
	{
	public:
		static void SetPosition(const maths::Vec3& pos);
		static void SetVelocity(const maths::Vec3& velocity);

		static maths::Vec3 GetPosition() { return m_Position; }
		static maths::Vec3 GetVelocity() { return m_Velocity; }
	private:
		static maths::Vec3 m_Position;
		static maths::Vec3 m_Velocity;
	};

}}