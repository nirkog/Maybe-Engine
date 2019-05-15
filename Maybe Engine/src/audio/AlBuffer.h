#pragma once

#include <vector>
#include <iostream>

#include "AL.h"
#include "MetaData.h"

namespace mb { namespace audio {

	class AlBuffer
	{
	public:
		AlBuffer();
		AlBuffer(char* data, MetaData metaData);
		~AlBuffer();

		void SetData(char* data, MetaData metaData);

		const unsigned int GetID() { return m_ID; }
	private:
		unsigned int m_ID;
	};

} }