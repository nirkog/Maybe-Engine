#pragma once

namespace mb { namespace audio {

	struct MetaData
	{
		char* format;
		int dataSize, sampleRate;
		short numChannels, bitsPerSample;
	};

} }