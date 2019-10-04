#pragma once

#include "AL.h"

#include <iostream>

namespace mb { namespace audio {

	class AlSource
	{
	public:
		AlSource();
		~AlSource();

		void Play(unsigned int buffer) const;

		const unsigned int GetID() { return m_ID; }
	private:
		unsigned int m_ID;
	};

} }