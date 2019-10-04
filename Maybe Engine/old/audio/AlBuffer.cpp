#include "AlBuffer.h"

namespace mb { namespace audio {

	AlBuffer::AlBuffer()
		: m_ID(0)
	{
		ALCall(alGenBuffers(1, &m_ID));
	}

	AlBuffer::AlBuffer(char* data, MetaData metaData)
		: m_ID(0)
	{
		ALCall(alGenBuffers(1, &m_ID));
		ALCall(SetData(data, metaData));
	}

	AlBuffer::~AlBuffer()
	{
		ALCall(alDeleteBuffers(1, &m_ID));
	}

	void AlBuffer::SetData(char* data, MetaData metaData)
	{
		ALCall(alBufferData(m_ID, AL_FORMAT_STEREO16, data, metaData.dataSize, metaData.sampleRate));
	}

} }